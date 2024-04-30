#ifndef LIBRARY_H
#define LIBRARY_H
#include "../model/Library.cpp"
#endif

class LedInternet : public Led
{
public:
   
    LedInternet(int pin) : Led(pin)
    {
        
    }
    LedInternet() : Led(17)
    {
        
    }
    ~LedInternet()
    {
        stopBlink();
        turnOff();
    }

    void actionOK() override
    {
        stopBlink();
        turnOn();
    }

    void actionError() override
    {
        blink(1);
        //sleep(3);
        //stopBlink();
    }


    
};

#ifdef TEST_LED_INTERNET
int main(int argc, const char** argv) {
    
    printf("Test LedInternet\n");
    LedInternet ledInternet;
    ledInternet.actionOK();
    sleep(5);
    ledInternet.actionError();


    return 0;
}
#endif
