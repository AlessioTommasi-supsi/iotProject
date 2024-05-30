#ifndef MASTERMODBUS_H
#define MASTERMODBUS_H

#include <Arduino.h>
#include <ModbusRTU.h>

class MasterModbus
{
private:
    ModbusRTU mb;

public:
    MasterModbus();
    static bool cbWrite(Modbus::ResultCode   event, uint16_t transactionId, void* data);
    void begin(HardwareSerial &serial);
    void readCoils(uint8_t slaveId, uint16_t startAddress, bool *coils, uint16_t quantity);
    void task();
};

#endif