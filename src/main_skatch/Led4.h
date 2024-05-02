#ifndef Led4_H
#define Led4_H

#include <Arduino.h>

class Led4
{
private:
    int pin;
    TaskHandle_t blinkTask;
    int blinkSpeed = 500; // in millisecondi

public:
    Led4(int pin);
    void turnOn();
    void turnOff();
    void stopBlink();
    virtual void actionOK();
    virtual void actionError();
};

#endif
