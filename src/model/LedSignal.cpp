#ifndef LIBRARY_H
#define LIBRARY_H
#include "../model/Library.cpp"
#endif

#include "SystemState.h"


class LedSignal : public Led
{
private:
    SystemState *systemState;

public:
    LedSignal(int pin) : Led(pin)
    {
        systemState = SystemState::getInstance();
        action();
    }
    LedSignal() : Led(22)
    {
        systemState = SystemState::getInstance();
        action();
    }
    ~LedSignal()
    {
        stopBlink();
        turnOff();
    }

    void actionError() override
    {
        stopBlink();
        turnOn();//resta acceso fino a quando non cambio stato!
        //std::cout << "LED ERROR!" << std::endl;
        //sleep(2);
        //turnOff();
    }

    void actionOK() override
    {
        switch (systemState->getState())
        {
        case State::INIT:
        case State::READ:
        case State::WRITE:
        case State::DUPLICATE:
            //faccio 1 lampeggio!
            turnOff();
            blink(2);
            sleep(1);
            stopBlink();
            break;
        default:
            //std::cout << "Error" << std::endl;
            actionError();
            break;
        }
    }

    void action(){
        actionOK();
    }
   
};

#ifdef TEST_LED_SIGNAL
void testLedSignal()
{
    printf("TesttestLedSignal\n");
    LedSignal led;
    SystemState *sys = SystemState::getInstance();
    sys->setState(State::INIT);
    led.actionOK();
    sleep(1);
    sys->setState(State::READ);
    led.actionOK();
    sleep(1);
    sys->setState(State::WRITE);
    led.actionOK();
    sleep(1);
    sys->setState(State::DUPLICATE);
    led.actionOK();
    sleep(1);
    sys->setState(State::ERROR);
    led.actionOK();
    sleep(1);
}

int main(int argc, const char **argv)
{
    testLedSignal();
    return 0;
}
#endif
