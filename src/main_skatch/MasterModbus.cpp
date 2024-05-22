#include "MasterModbus.h"

// link prof: se non funziona questo: https://embeddedthere.com/how-to-interface-esp32-with-rs485-modbus-sensors-with-example-code/#Modbus_Library_Functions

MasterModbus::MasterModbus() {}

void MasterModbus::begin(HardwareSerial &serial)
{
    mb.begin(&serial);
    mb.master();
}

bool MasterModbus::cbWrite(Modbus::ResultCode event, uint16_t transactionId, void *data)
{
#ifdef ESP8266
    Serial.printf_P("Request result: 0x%02X, Mem: %d\n", event, ESP.getFreeHeap());
#elif ESP32
    Serial.printf_P("Request result: 0x%02X, Mem: %d\n", event, ESP.getFreeHeap());
#else
    Serial.print("Request result: 0x");
    Serial.print(event, HEX);
#endif
    return true;
}

void MasterModbus::readCoils(uint8_t slaveId, uint16_t startAddress, bool *coils, uint16_t quantity)
{
    mb.readCoil(slaveId, startAddress, coils, quantity, cbWrite);
}

void MasterModbus::task()
{
    mb.task();
}