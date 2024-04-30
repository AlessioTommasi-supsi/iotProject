
#ifndef LIBRARY_H
#define LIBRARY_H
#include "../model/Library.cpp"
#endif


class ButtonWrite : public Button
{
public:
    ButtonWrite(int pin) : Button(pin)
    {
    }
    ButtonWrite() : Button(23)
    {
    }
    ~ButtonWrite(){
        stopListening();
    }

    void actionPressed() override
    {
        SystemState *sys = SystemState::getInstance();
        switch (sys->getState())
        {
        case State::INIT:
        case State::READ:
            sys->setState(State::WRITE);
            break;
        case State::WRITE:
            sys->setState(State::DUPLICATE);
            break;
        case State::DUPLICATE:
            sys->setState(State::READ);
            break;
        case State::ERROR:
            sys->setState(State::READ);//quando sono in error devo schiacciare il bottone per tornare in read!
            break;

        default:
            sys->setState(State::ERROR);
        }

        usleep(100000); // Attendi 0,1 secondo prima di poter premere nuovamente il bottone!
    }

};

#ifdef TEST_BUTTON_WRITE

void testButtonWrite1()
{
    SystemState *sys = SystemState::getInstance();
    sys->setState(State::INIT);

    printf("Test ButtonWrite\n");
    ButtonWrite buttonWrite;
    buttonWrite.startListening();
    while (true)
    {
        std::cout << "Lo stato del sistema è " << sys->getStateString() << std::endl;

        usleep(500000); //aspetta 1/2 secondo
    }
    
    //sleep(10);
    buttonWrite.stopListening();
}

int main(int argc, const char **argv)
{
    wiringPiSetupGpio(); // Inizializzazione di WiringPi
    testButtonWrite1();

    return 0;
}
#endif
