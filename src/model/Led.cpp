#ifndef LIBRARY_H
#define LIBRARY_H
#include "../model/Library.cpp"
#endif

class Led
{
private:
    int GPIO_pin;
    std::atomic<bool> isBlinking;
    std::thread blinkThread;
    int blinkSpeed = 500;// in millisecondi

    void blinkThreadFunction(){
        while (isBlinking)
        {
            turnOn();
            usleep(blinkSpeed*1000);
            turnOff();
            usleep(blinkSpeed*1000);
        }
    }

public:
    Led(int GPIO_pin){
        blinkSpeed = blinkSpeed;
        this->GPIO_pin = GPIO_pin;
        isBlinking = false;
    }

    void turnOn(){
        std::string command = "raspi-gpio set " + std::to_string(GPIO_pin) + " op dh";
        system(command.c_str());
    }

    void turnOff(){
        std::string command = "raspi-gpio set " + std::to_string(GPIO_pin) + " op dl";
        system(command.c_str());
    }

    void blink(){
        if (!isBlinking)
        {
            isBlinking = true;
            blinkThread = std::thread(&Led::blinkThreadFunction, this);
        }
    }
    void blink(float speed)
    {
        // se metto 10 ad esempio voglio che il led in un secondo si accenda e spenga 10 volte
        blinkSpeed = (int) 1000/(speed*2);

        if (!isBlinking)
        {
            isBlinking = true;
            blinkThread = std::thread(&Led::blinkThreadFunction, this);
        }
    }

    void stopBlink(){
        if (isBlinking)
        {
            isBlinking = false;
            if (blinkThread.joinable())
            {
                blinkThread.join();
            }
        }
    }

    virtual void actionOK()
    {
        stopBlink();
        turnOn();
    }

    virtual void actionError()
    {
        turnOff();
    }
};

#ifdef TEST_LED

void test1(){
    Led led(4);
    

    led.blink(1);/*si accende e spegne 1 volte in un secondo*/
    sleep(5);
    led.stopBlink();
    
}
void testLed()
{
    Led ledInternet(17);
    Led ledScrittura(27);
    Led ledError(22);

    ledInternet.blink(1); /*si accende e spegne 1 volte in un secondo*/
    ledScrittura.blink(2); /*si accende e spegne 2 volte in un secondo*/
    ledError.blink(3); /*si accende e spenge 3 volte in un secondo*/
    sleep(5);
    ledInternet.stopBlink();
    ledScrittura.stopBlink();
    ledError.stopBlink();
}


int main() {
    testLed();
    return 0;
}
#endif