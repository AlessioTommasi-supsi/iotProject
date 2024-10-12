#ifndef LedEsp32_H
#define LedEsp32_H

#include <Arduino.h>
#include "Component.h"

class LedEsp32 : Component
{
private:
    int pin;
    TaskHandle_t blinkTask;
    int blinkSpeed = 500; // in millisecondi

public:
    LedEsp32(int pin);
    ~LedEsp32();
    void turnOn();
    void turnOff();
    void blink();
    void blink(float speed);
    void stopBlink();
    void actionOK();
    void actionError();
    void action() override;

    // Static member function for the task
    static void blinkTaskFunction(void *parameter);
};

#endif
