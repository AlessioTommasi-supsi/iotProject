#include "ModbusRTUMaster.h"

ModbusRTUMaster::ModbusRTUMaster(HardwareSerial& serial, uint8_t dePin) {
  _hardwareSerial = &serial;
  _serial = &serial;
  _dePin = dePin;
}


void ModbusRTUMaster::setTimeout(unsigned long timeout) {
  _responseTimeout = timeout;
}

void ModbusRTUMaster::begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert) {
  if (_hardwareSerial) {
    _calculateTimeouts(baud, config);
    _hardwareSerial->begin(baud, config, rxPin, txPin, invert);
  }
  if (_dePin != NO_DE_PIN) {
    pinMode(_dePin, OUTPUT);
    digitalWrite(_dePin, LOW);
  }
  _clearRxBuffer();
}

bool ModbusRTUMaster::readHoldingRegisters(uint8_t id, uint16_t startAddress, uint16_t *buf, uint16_t quantity) {
  const uint8_t functionCode = 3;
  uint8_t byteCount = quantity * 2;
  if (id < 1 || id > 247 || !buf || quantity == 0 || quantity > 125) return false;
  _buf[0] = id;
  _buf[1] = functionCode;
  _buf[2] = highByte(startAddress);
  _buf[3] = lowByte(startAddress);
  _buf[4] = highByte(quantity);
  _buf[5] = lowByte(quantity);
  _writeRequest(6);
  uint16_t responseLength = _readResponse(id, functionCode);
  if (responseLength != (uint16_t)(3 + byteCount) || _buf[2] != byteCount) return false;
  for (uint16_t i = 0; i < quantity; i++) {
    buf[i] = _bytesToWord(_buf[3 + (i * 2)], _buf[4 + (i * 2)]);
  }
  return true;
}

bool ModbusRTUMaster::getTimeoutFlag() {
  return _timeoutFlag;
}

void ModbusRTUMaster::clearTimeoutFlag() {
  _timeoutFlag = 0;
}

uint8_t ModbusRTUMaster::getExceptionResponse() {
  return _exceptionResponse;
}

void ModbusRTUMaster::_writeRequest(uint8_t len) {
  uint16_t crc = _crc(len);
  _buf[len] = lowByte(crc);
  _buf[len + 1] = highByte(crc);
  if (_dePin != NO_DE_PIN) digitalWrite(_dePin, HIGH);
  _serial->write(_buf, len + 2);
  _serial->flush();
  if (_dePin != NO_DE_PIN) digitalWrite(_dePin, LOW);
}

uint16_t ModbusRTUMaster::_readResponse(uint8_t id, uint8_t functionCode) {
  unsigned long startTime = millis();
  uint16_t numBytes = 0;
  while (!_serial->available()) {
    if (millis() - startTime >= _responseTimeout) {
      _timeoutFlag = true;
      return 0;
    }
  }
  do {
    if (_serial->available()) {
      startTime = micros();
      _buf[numBytes] = _serial->read();
      numBytes++;
    }
  } while (micros() - startTime <= _charTimeout && numBytes < MODBUS_RTU_MASTER_BUF_SIZE);
  while (micros() - startTime < _frameTimeout);
  if (_serial->available() || _buf[0] != id || (_buf[1] != functionCode && _buf[1] != (functionCode + 128)) || _crc(numBytes - 2) != _bytesToWord(_buf[numBytes - 1], _buf[numBytes - 2])) return 0;
  else if (_buf[1] == (functionCode + 128)) {
    _exceptionResponse = _buf[2];
    return 0;
  }
  return (numBytes - 2);
}

void ModbusRTUMaster::_clearRxBuffer() {
  unsigned long startTime = micros();
  do {
    if (_serial->available() > 0) {
      startTime = micros();
      _serial->read();
    }
  } while (micros() - startTime < _frameTimeout);
}

void ModbusRTUMaster::_calculateTimeouts(unsigned long baud, uint32_t config) {
  unsigned long bitsPerChar;
  if (config == SERIAL_8E2 || config == SERIAL_8O2) bitsPerChar = 12;
  else if (config == SERIAL_8N2 || config == SERIAL_8E1 || config == SERIAL_8O1) bitsPerChar = 11;
  else bitsPerChar = 10;
  if (baud <= 19200) {
    _charTimeout = (bitsPerChar * 2500000) / baud;
    _frameTimeout = (bitsPerChar * 4500000) / baud;
  }
  else {
    _charTimeout = (bitsPerChar * 1000000) / baud + 750;
    _frameTimeout = (bitsPerChar * 1000000) / baud + 1750;
  }
}

uint16_t ModbusRTUMaster::_crc(uint8_t len) {
  uint16_t value = 0xFFFF;
  for (uint8_t i = 0; i < len; i++) {
    value ^= (uint16_t)_buf[i];
    for (uint8_t j = 0; j < 8; j++) {
      bool lsb = value & 1;
      value >>= 1;
      if (lsb == true) value ^= 0xA001;
    }
  }
  return value;
}

uint16_t ModbusRTUMaster::_bytesToWord(uint8_t high, uint8_t low) {
  return (high << 8) | low;
}