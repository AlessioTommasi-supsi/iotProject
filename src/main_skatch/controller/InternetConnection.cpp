#ifndef LIBRARY_H
#define LIBRARY_H
#include "../model/Library.cpp"
#endif

class InternetConnection
{
private:
    bool isStopped;

    bool isConnected()
    {
        int result = system("ping -c 1 google.com > /dev/null 2>&1");

        return result == 0;
    }

public:

    Led *led;
    InternetConnection()
    {
        led = new LedInternet();
    }

    ~InternetConnection()
    {
        stopConnectionCheck();
        delete led;
    }

    void checkConnectionThreadFunction()
    {
        while (!isStopped)
        {
            bool connected = isConnected(); // Verifica se il dispositivo è connesso a internet
            if (connected)
            {
                led->actionOK();
            }
            else
            {
                led->actionError();
            }
            std::this_thread::sleep_for(std::chrono::seconds(5)); /*NOTA: puo accadere che programma main termina mentre sono ancora in sleep!*/
        }
    }

    void checkConnection()
    {
        isStopped = false;
        std::thread connectionThread(&InternetConnection::checkConnectionThreadFunction, this);
        connectionThread.detach();
    }
    void stopConnectionCheck()
    {
        led->turnOff();
        isStopped = true; 
    }

};



#ifdef TEST_INTERNET

void testInternetConnection1()
{
    InternetConnection connection;
    connection.checkConnection(); // Avvia il thread per verificare la connessione internet e controllare il LED

    // Il programma continua a eseguire altre operazioni qui...

    // Attendiamo che il thread di controllo della connessione continui a funzionare in background
    sleep(10);
    //connection.led->turnOff();
    connection.stopConnectionCheck();

}

void testInternetConnection2()
{
    printf("Test InternetConnection\n");
}

int main()
{
    testInternetConnection1();
}
#endif
