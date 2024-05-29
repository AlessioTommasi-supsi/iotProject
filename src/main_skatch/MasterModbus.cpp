#include "MasterModbus.h"

// link prof: se non funziona questo: https://embeddedthere.com/how-to-interface-esp32-with-rs485-modbus-sensors-with-example-code/#Modbus_Library_Functions

MasterModbus::MasterModbus(): modbus(Serial1, dePin){
    begin();
}

void MasterModbus::processError()
{
    if (modbus.getTimeoutFlag())
    {
        Serial.println(F("Connection timed out"));
        modbus.clearTimeoutFlag();
    }
    else if (modbus.getExceptionResponse() != 0)
    {
        Serial.print(F("Received exception response: "));
        Serial.print(modbus.getExceptionResponse());
        switch (modbus.getExceptionResponse())
        {
        case 1:
            Serial.println(F(" - Illegal function"));
            break;
        case 2:
            Serial.println(F(" - Illegal data address"));
            break;
        case 3:
            Serial.println(F(" - Illegal data value"));
            break;
        case 4:
            Serial.println(F(" - Server device failure"));
            break;
        default:
            Serial.println();
            break;
        }
        modbus.clearExceptionResponse();
    }
    else
    {
        Serial.println("An error occurred");
    }
}

void MasterModbus::begin()
{
    Serial.begin(9600);
    Serial.setTimeout(100);
    while (!Serial)
    {
    }

    modbus.begin(9600, SERIAL_8N1, rxPin, txPin, false);
    modbus.setTimeout(100);
    Serial.print(F("Modbus serial port configuration: 9600"));
    Serial.println(F("-8-N-1"));
    Serial.println();
}

uint32_t MasterModbus::readHoldingRegisters(uint16_t address){
    uint16_t holdingRegisters[2];
    uint8_t success = modbus.readHoldingRegisters(1, address - 1, holdingRegisters, 2);
    uint32_t value = 0;
    if (success)
    {

        // Combine the two 16-bit registers into a 32-bit integer
        value = holdingRegisters[0] << 16 | holdingRegisters[1];
        Serial.print(F("Received value: "));
        Serial.println(value);
    }
    else
    {
        processError();
    }
    return value;
}

float MasterModbus::readHoldingFloatRegisters(uint16_t address)
{
    uint16_t holdingRegisters[2];
    uint8_t success = modbus.readHoldingRegisters(1, address - 1, holdingRegisters, 2);
    float value = 0;
    if (success)
    {

        // Combine the two 16-bit registers into a 32-bit integer
        uint32_t combined = ((uint32_t)holdingRegisters[0] << 16) | holdingRegisters[1];
        // Convert the combined 32-bit integer to a float
        memcpy(&value, &combined, sizeof(value));

        Serial.print(F("Read value of "));
        Serial.print(value, 6);
        Serial.print(F(" from holding register address "));
        Serial.println(address);
    }
    else
    {
        processError();
    }
    return value;
}

int MasterModbus::readHoldingIntRegisters(uint16_t address)
{
    uint16_t holdingRegister;
    uint8_t success = modbus.readHoldingRegisters(1, address - 1, &holdingRegister, 1);
    if (success)
    {
        Serial.print(F("Read value of "));
        Serial.print(holdingRegister);
        Serial.print(F(" from holding register address "));
        Serial.println(address);
    }
    else
    {
        processError();
    }
    return holdingRegister;
}

void MasterModbus::task()
{
    readHoldingFloatRegisters(122);
    readHoldingIntRegisters(500);
}