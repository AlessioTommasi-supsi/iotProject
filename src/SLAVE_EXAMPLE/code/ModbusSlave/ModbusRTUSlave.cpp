#include "ModbusRTUSlave.h"
#include "Utils.h"

#define MAX_HOLDING_REGISTERS_QUANTITY 20
#define TOTAL_REGISTERS 1000

ModbusRTUSlave::ModbusRTUSlave(HardwareSerial& serial, uint8_t dePin) {
  _hardwareSerial = &serial;
  _serial = &serial;
  _holdingRegisters = 0;
  _dePin = dePin;
}

void ModbusRTUSlave::configureHoldingRegisters(uint16_t holdingRegisters[], uint16_t numHoldingRegisters) {
  _holdingRegisters = holdingRegisters;
  _numHoldingRegisters = numHoldingRegisters;
}

void ModbusRTUSlave::begin(uint8_t id, unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert) {
  if (id >= 1 && id <= 247) _id = id;
  else _id = NO_ID;
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

void ModbusRTUSlave::poll() {
  if (_serial->available()) {
    if (_readRequest()) {
      switch (_buf[1]) {
        case 3:
          _processReadHoldingRegisters();
          break;
        default:
          _exceptionResponse(1);
          break;
      }
    }
  }
}

void ModbusRTUSlave::setFillHoldingRegistersCallback(void (*callback)(uint16_t, uint16_t)) {
    _fillHoldingRegistersCallback = callback;
   
}

void ModbusRTUSlave::updateHoldingRegistersSlave(uint16_t* data, uint16_t quantity) {   
    
    for (uint16_t i = 0; i < quantity; i++) {
       _holdingRegistersSlave[i] = data[i];
    }
}

void ModbusRTUSlave::insertIntoHoldingRegistersSlave(uint16_t address, float data, bool swap) {
    if (data != static_cast<int>(data)) { // If data is a float (not an integer)
        uint16_t reg1, reg2;
        convertToRegisters(data, reg1, reg2);

        if(!swap){
          // Store the integer and fractional parts in two different registers
          _holdingRegistersSlave[address - 1] = reg1;
          _holdingRegistersSlave[address] = reg2;
        }else{
          // Store the integer and fractional parts in two different registers
          _holdingRegistersSlave[address - 1] = reg2;
          _holdingRegistersSlave[address] = reg1;
        }
    } else { // If data is an integer, store it in the first register only
        uint16_t intPart = static_cast<uint16_t>(data); // Entire integer part
        _holdingRegistersSlave[address - 1] = intPart;        
    }
}


void ModbusRTUSlave::_processReadHoldingRegisters() {
   
  uint16_t startAddress = _bytesToWord(_buf[2], _buf[3]);
  uint16_t quantity = _bytesToWord(_buf[4], _buf[5]);
  
  // Controlla che la richiesta sia valida: la quantità deve essere >=1 e lo startAddress
  // più la quantità non devono superare il totale dei registri disponibili.
  if (quantity < 1 || (startAddress + quantity) > TOTAL_REGISTERS) {
    _exceptionResponse(3); // Quantità o indirizzo non valido
    return;
  }
  
  // In questo esempio, puoi chiamare la callback per aggiornare i registri del blocco se necessario.
  // La callback potrebbe popolare _holdingRegistersSlave in base allo startAddress.
  _fillHoldingRegistersCallback(startAddress, quantity);

  // Prepara il messaggio di risposta copiando direttamente dall'array dei registri,
  // usando lo startAddress come offset!
  _buf[2] = quantity * 2;
  for (uint16_t i = 0; i < quantity; i++) {
    uint16_t regIndex = startAddress + i;
    _buf[3 + (i * 2)] = highByte(_holdingRegistersSlave[regIndex]);
    _buf[4 + (i * 2)] = lowByte(_holdingRegistersSlave[regIndex]);
  }
  _writeResponse(3 + _buf[2]);
}

bool ModbusRTUSlave::_readRequest() {
  uint16_t numBytes = 0;
  unsigned long startTime = 0;
  do {
    if (_serial->available()) {
      startTime = micros();
      _buf[numBytes] = _serial->read();
      numBytes++;
    }
  } while (micros() - startTime <= _charTimeout && numBytes < MODBUS_RTU_SLAVE_BUF_SIZE);
  while (micros() - startTime < _frameTimeout);
  if (!_serial->available() && (_buf[0] == _id || _buf[0] == 0) && _crc(numBytes - 2) == _bytesToWord(_buf[numBytes - 1], _buf[numBytes - 2])) return true;
  else return false;
}

void ModbusRTUSlave::_writeResponse(uint8_t len) {
  if (_buf[0] != 0) {
    uint16_t crc = _crc(len);
    _buf[len] = lowByte(crc);
    _buf[len + 1] = highByte(crc);
    if (_dePin != NO_DE_PIN) digitalWrite(_dePin, HIGH);
    _serial->write(_buf, len + 2);
    _serial->flush();
    if (_dePin != NO_DE_PIN) digitalWrite(_dePin, LOW);
    while(_serial->available()) {
      _serial->read();
    }
  }
}

void ModbusRTUSlave::_exceptionResponse(uint8_t code) {
  _buf[1] |= 0x80;
  _buf[2] = code;
  _writeResponse(3);
}

void ModbusRTUSlave::_clearRxBuffer() {
  unsigned long startTime = micros();
  do {
    if (_serial->available()) {
      startTime = micros();
      _serial->read();
    }
  } while (micros() - startTime < _frameTimeout);
}

void ModbusRTUSlave::_calculateTimeouts(unsigned long baud, uint32_t config) {
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

uint16_t ModbusRTUSlave::_crc(uint8_t len) {
  uint16_t value = 0xFFFF;
  for (uint8_t i = 0; i < len; i++) {
    value ^= (uint16_t)_buf[i];
    for (uint8_t j = 0; j < 8; j++) {
      bool lsb = value & 1;
      value >>= 1;
      if (lsb) value ^= 0xA001;
    }
  }
  return value;
}

uint16_t ModbusRTUSlave::_bytesToWord(uint8_t high, uint8_t low) {
  return (high << 8) | low;
}