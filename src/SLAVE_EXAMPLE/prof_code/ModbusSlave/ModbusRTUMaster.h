#ifndef ModbusRTUMaster_h
#define ModbusRTUMaster_h

#define MODBUS_RTU_MASTER_BUF_SIZE 256
#define NO_DE_PIN 255

#include "Arduino.h"

class ModbusRTUMaster {
  public:
    ModbusRTUMaster(HardwareSerial& serial, uint8_t dePin = NO_DE_PIN);
    void setTimeout(unsigned long timeout);
    void begin(unsigned long baud, uint32_t config = SERIAL_8N1, int8_t rxPin = -1, int8_t txPin = -1, bool invert = false);
    bool readHoldingRegisters(uint8_t id, uint16_t startAddress, uint16_t *buf, uint16_t quantity);
    bool getTimeoutFlag();
    void clearTimeoutFlag();
    uint8_t getExceptionResponse();

  private:
    HardwareSerial *_hardwareSerial;
    Stream *_serial;
    uint8_t _dePin;
    uint8_t _buf[MODBUS_RTU_MASTER_BUF_SIZE];
    unsigned long _charTimeout;
    unsigned long _frameTimeout;
    unsigned long _responseTimeout = 100;
    bool _timeoutFlag = false;
    uint8_t _exceptionResponse = 0;
    
    void _writeRequest(uint8_t len);
    uint16_t _readResponse(uint8_t id, uint8_t function);
    void _clearRxBuffer();

    void _calculateTimeouts(unsigned long baud, uint32_t config);
    uint16_t _crc(uint8_t len);
    uint16_t _bytesToWord(uint8_t high, uint8_t low);
};

#endif
