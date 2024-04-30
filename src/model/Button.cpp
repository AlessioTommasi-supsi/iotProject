#ifndef LIBRARY_H
#define LIBRARY_H
#include "../model/Library.cpp"
#endif

class Button
{
private:
    int GPIO_pin;
    std::atomic<bool> isListening;
    std::thread listenThread;

    void listenThreadFunction()
    {
        while (isListening)
        {
            if (digitalRead(GPIO_pin) == HIGH)
            {
                // Il bottone è stato premuto
                actionPressed();
            }
            usleep(100000); // Controllo ogni 0,1 secondi
        }
    }

public:
    virtual void actionPressed()
    {
        // Azione da eseguire quando il bottone viene premuto
        std::cout << "Bottone premuto!" << std::endl;
        //usleep(100000); // Attendi 0.1 secondi prima di poter premere nuovamente il bottone
        sleep(1); // Attendi 1 secondo prima di poter premere nuovamente il bottone
    }

    Button(int GPIO_pin) : GPIO_pin(GPIO_pin), isListening(false) {}

    void startListening()
    {
        if (!isListening)
        {
            isListening = true;
            listenThread = std::thread([this]() { this->listenThreadFunction(); });

        }
    }

    void stopListening()
    {
        if (isListening)
        {
            isListening = false;
            if (listenThread.joinable())
            {
                listenThread.join();
            }
        }
    }
};

// Test
#ifdef TEST_BUTTON
void testButton()
{
    Button button(23); // Assuming button is connected to GPIO pin 17
    button.startListening();
    sleep(50); // Listen for button press for 50 seconds
    button.stopListening();
}

int main()
{
    wiringPiSetupGpio(); // Inizializzazione di WiringPi
    testButton();
    return 0;
}
#endif