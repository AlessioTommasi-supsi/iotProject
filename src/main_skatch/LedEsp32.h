#ifndef LedEsp32_H
#define LedEsp32_H

#include <Arduino.h>

class LedEsp32
{
private:
    int pin;
    TaskHandle_t blinkTask;
    int blinkSpeed = 500; // in millisecondi

    

public:

    LedEsp32(int pin);
    void turnOn();
    void turnOff();
    void stopBlink();
    virtual void actionOK();
    virtual void actionError();
};

#endif
