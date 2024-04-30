#ifndef LIBRARY_H
#define LIBRARY_H
#include "../model/Library.cpp"
#endif

#include "SystemState.h"


class LedWrite : public Led
{
private:
    SystemState *systemState;
public:
    LedWrite(int pin) : Led(pin)
    {
        systemState = SystemState::getInstance();
        activate();
    }
    LedWrite() : Led(27)
    {
        systemState = SystemState::getInstance();
        activate();
    }
    ~LedWrite()
    {
        stopBlink();
        turnOff();
    }

    void actionOK() override
    {
        switch (systemState->getState()) 
        {
        case State::INIT:
        case State::READ:
            stopBlink();
            turnOff();
            break;
        case State::WRITE:
            stopBlink();
            turnOn();
            break;
        case State::DUPLICATE:
            blink(2);
            break;
        default:
            actionError();
            break;
        }
    }

    void actionError() override
    {
        blink(1);
        sleep(3);
        stopBlink();
    }

    void activate()
    {
        actionOK();
    }

    void check()
    {
        actionOK();
    }

    void action()
    {
        actionOK();
    }

};



#ifdef TEST_LED_WRITE
void testLedWrite()
{
    printf("Test Led\n");
    LedWrite ledInternet;
    SystemState *sys = SystemState::getInstance();
    sys->setLedWrite(&ledInternet);

    sys->setState(State::INIT);
    sleep(1);
    sys->setState(State::READ);
    sleep(1);
    sys->setState(State::WRITE);
    sleep(3);
    sys->setState(State::DUPLICATE);
    sleep(3);
 
}

void testLedWrite2()
{
    printf("Test LedInternet\n");
    LedWrite ledInternet;
    SystemState *sys = SystemState::getInstance();
    sys->setState(State::INIT);
    ledInternet.actionOK();
    sleep(1);
    sys->setState(State::READ);
    ledInternet.actionOK();
    sleep(1);
    sys->setState(State::WRITE);
    ledInternet.actionOK();
    sleep(3);
    sys->setState(State::DUPLICATE);
    ledInternet.actionOK();
    sleep(3);

    ledInternet.actionError();
}

int main(int argc, const char **argv)
{    
    testLedWrite();
    return 0;
}
#endif
