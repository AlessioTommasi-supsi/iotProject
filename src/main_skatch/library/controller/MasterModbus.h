#ifndef MASTERMODBUS_H
#define MASTERMODBUS_H

#include <ModbusRTUMaster.h>

class MasterModbus
{
private:
    
public:
    const uint8_t rxPin = 16;
    const uint8_t txPin = 17;
    const uint8_t dePin = 4;

    ModbusRTUMaster modbus;

    MasterModbus();
    void begin();
    uint32_t readHoldingRegisters(uint16_t address);
    float readHoldingFloatRegisters(uint16_t address);
    int readHoldingIntRegisters(uint16_t address);
    void task();
    void processError();
};

#endif