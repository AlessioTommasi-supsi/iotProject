#ifndef SLAVEMODBUS_H
#define SLAVEMODBUS_H

#include <Arduino.h>
#include <ModbusRTU.h>

class SlaveModbus
{
private:
    ModbusRTU mb;

public:
    SlaveModbus(uint8_t slaveId);
    void begin(HardwareSerial &serial);
    void addHoldingRegister(uint16_t address);
    void setHoldingRegisterValue(uint16_t address, uint16_t value);
    void task();
};

#endif