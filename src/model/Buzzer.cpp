#ifndef LIBRARY_H
#define LIBRARY_H
#include "../model/Library.cpp"
#endif

#include "SystemState.h"

class Buzzer {
private:
    int GPIO_pin;
    SystemState *systemState;

public:
    Buzzer(int GPIO_pin){
        this->GPIO_pin = GPIO_pin;
        systemState = SystemState::getInstance();
    }
    Buzzer()
    {
        this->GPIO_pin = 4;
        systemState = SystemState::getInstance();
    }

    void turnOn(){
        std::string command = "raspi-gpio set " + std::to_string(GPIO_pin) + " op dh";
        system(command.c_str());
    }

    void turnOff(){
        std::string command = "raspi-gpio set " + std::to_string(GPIO_pin) + " op dl";
        system(command.c_str());
    }
    /*
    * durata in millisecondi in cui buzzer e' acceso!
    */
    void beep(int duration){
        turnOn();
        usleep(duration*1000);
        turnOff();
    }

    /*
    * pausa dopo quanto devo ripetere!
    */
    void beep(int duration, int times, int pause){
        for (int i = 0; i < times; i++)
        {
            beep(duration);
            usleep(pause*1000);
        }
    }

    void badge_ok(){
        beep(500);
    }

    void badge_error(){
        beep(100, 3, 100);
    }

    void startupMusic(){
        beep(300, 1, 300);
        usleep(200 * 1000);
        beep(100, 2, 100);
    }


    void action()
    {
        switch (systemState->getState())
        {
        case State::INIT:
        case State::READ:
        case State::WRITE:
        case State::DUPLICATE:
            // faccio 1 lampeggio!
            badge_ok();
            break;
        default:
            std::cout << "Error" << std::endl;
            badge_error();
            break;
        }
    }
};
#ifdef TEST_BUZZER

void Buzzertest1()
{
    Buzzer buzzer(2);
    buzzer.beep(100, 5, 100);
    buzzer.beep(500, 3, 100);
}

void Buzzertest2()
{
    Buzzer buzzer(2);
    buzzer.turnOn();
    sleep(1);
    buzzer.turnOff();
}

void Buzzertest3()
{
    Buzzer buzzer(2);
    buzzer.beep(500);
}

void Buzzertest4(){
    Buzzer buzzer(2);
    buzzer.badge_error();
}

void Buzzertest5()
{
    Buzzer buzzer(4);
    buzzer.startupMusic();
}

int main(){
    Buzzertest5();
}

#endif