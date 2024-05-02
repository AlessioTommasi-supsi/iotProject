#include "Led4.h"

Led4::Led4(int pin)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void Led4::turnOn()
{
    digitalWrite(pin, HIGH);
}

void Led4::turnOff()
{
    digitalWrite(pin, LOW);
}

void Led4::actionOK()
{
}

void Led4::actionError()
{
}