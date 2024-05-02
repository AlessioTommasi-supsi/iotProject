#include "LedEsp32.h"


LedEsp32::LedEsp32(int pin)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void LedEsp32::turnOn()
{
    digitalWrite(pin, HIGH);
}

void LedEsp32::turnOff()
{
    digitalWrite(pin, LOW);
}

void LedEsp32::actionOK()
{

}

void LedEsp32::actionError()
{
    
}