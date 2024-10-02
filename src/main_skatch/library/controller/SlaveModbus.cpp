#include "SlaveModbus.h"

// ModbusRTUSlave
//  -> BEGIN DELLA SERIAL
//      POOL
// CAMBIA PORTE SLAVE!!

SlaveModbus::SlaveModbus(int rxPin, int txPin)
{
    REGN = 100;
    Serial2.begin(115200, SERIAL_8N1, rxPin, txPin);
    mb.slave(1);
    mb.begin(&Serial2);
    mb.addHreg(REGN);
    mb.Hreg(REGN, 100);
    is_stopped = false;
    loopTask();
}

SlaveModbus::SlaveModbus(uint8_t slaveId, int rxPin, int txPin)
{
    Serial2.begin(9600, SERIAL_8N1, rxPin, txPin);
    mb.slave(slaveId);
}

void SlaveModbus::begin(HardwareSerial &serial)
{
    mb.begin(&serial);
}

void SlaveModbus::addHoldingRegister(uint16_t address)
{
    mb.addHreg(address);
}

void SlaveModbus::setHoldingRegisterValue(uint16_t address, uint16_t value)
{
    mb.Hreg(address, value);
}

void SlaveModbus::task()
{
    mb.task();
}

void SlaveModbus::loopTask()
{
    while (!is_stopped)
    {
        task();
        yield();
        delay(100);
    }
}
