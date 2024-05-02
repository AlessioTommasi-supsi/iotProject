#ifndef Led5_H
#define Led5_H

#include <Arduino.h>

class Led5
{
private:
    int pin;
    TaskHandle_t blinkTask;
    int blinkSpeed = 500; // in millisecondi

public:
    Led5(int pin);
    void turnOn();
    void turnOff();
    void stopBlink();
    virtual void actionOK();
    virtual void actionError();
};

#endif
