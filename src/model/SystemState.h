#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H



enum class State
{
    INIT,
    READ,
    WRITE,
    DUPLICATE,
    ERROR
};

class SystemState
{
private:
    static SystemState *instance;
    static std::mutex mutex;
    State state = State::INIT;
    Led *ledWrite; // led che deve cambiare non appena viene cambiato lo stato del sistema!
    Led *ledSignal;

    static std::string error_message;

    SystemState() {}

public:
    

    static SystemState *getInstance();

    void update();

    void setState(State newState);

    void setLedWrite(Led *led);

    void setLedSignal(Led *led);

    State getState();

    std::string getStateString() ;

    void setError(std::string message);
    
    std::string getError();

    void sendErrorMail();
};

#endif // SYSTEMSTATE_H