/*
#include "SlaveModbus.h"
//ModbusRTUSlave
//  -> BEGIN DELLA SERIAL
//      POOL
// CAMBIA PORTE  SLAVE!!

SlaveModbus::SlaveModbus()
{
    REGN = 100;
    Serial.begin(9600, SERIAL_8N1);//qui problema devo definire pin della porta seriale!
    mb.slave(1);
    mb.begin(&Serial);
    mb.addHreg(REGN);
    mb.Hreg(REGN, 100);
    is_stopped = false;
    loopTask();
}

SlaveModbus::SlaveModbus(uint8_t slaveId)
{
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
    }
    
}
*/
