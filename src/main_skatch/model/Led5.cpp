#include "Led5.h"

Led5::Led5(int pin)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void Led5::turnOn()
{
    digitalWrite(pin, HIGH);
}

void Led5::turnOff()
{
    digitalWrite(pin, LOW);
}

void Led5::actionOK()
{
}

void Led5::actionError()
{
}