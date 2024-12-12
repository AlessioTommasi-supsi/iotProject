#ifndef ModbusRTUSlave_h
#define ModbusRTUSlave_h

#define MODBUS_RTU_SLAVE_BUF_SIZE 256
#define NO_DE_PIN 255
#define NO_ID 0

#include "Arduino.h"

class ModbusRTUSlave {
  public:
    ModbusRTUSlave(HardwareSerial& serial, uint8_t dePin = NO_DE_PIN);
    void setFillHoldingRegistersCallback(void (*callback)(uint16_t, uint16_t));
    void configureHoldingRegisters(uint16_t holdingRegisters[], uint16_t numHoldingRegisters);
    void updateHoldingRegistersSlave(uint16_t* data, uint16_t quantity);
    void begin(uint8_t id, unsigned long baud, uint32_t config = SERIAL_8N1, int8_t rxPin = -1, int8_t txPin = -1, bool invert = false);
 
    void poll();
    
  private:
    HardwareSerial *_hardwareSerial;
    Stream *_serial;
    uint8_t _dePin;
    uint8_t _buf[MODBUS_RTU_SLAVE_BUF_SIZE];
    uint16_t *_holdingRegisters;
    uint16_t _numHoldingRegisters = 0;
    uint8_t _id;
    unsigned long _charTimeout;
    unsigned long _frameTimeout;
    uint16_t _holdingRegistersSlave[20];

    void (*_fillHoldingRegistersCallback)(uint16_t, uint16_t);

    void _processReadHoldingRegisters();

    bool _readRequest();
    void _writeResponse(uint8_t len);
    void _exceptionResponse(uint8_t code);
    void _clearRxBuffer();

    void _calculateTimeouts(unsigned long baud, uint32_t config);
    uint16_t _crc(uint8_t len);
    uint16_t _bytesToWord(uint8_t high, uint8_t low);
};

#endif
