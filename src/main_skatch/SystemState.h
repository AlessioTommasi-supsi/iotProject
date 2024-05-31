#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H

#include <vector>
#include <Arduino.h>
#include "MasterModbus.h"

enum class State
{
    INIT,
    MASTER,
    SLAVE,
    ERROR
};

class SystemState
{
private:
    static SystemState *instance;
    State state = State::INIT;

    static char * error_message;
    
    std::vector<int> address;
    std::vector<float> value;

    SystemState() {}

public:
    static MasterModbus *masterModbus;


    static SystemState *getInstance();

    ~SystemState();

    void update();

    void setState(State newState);

    State getState();

    char * getStateString();

    void setError(char * message);

    char * getError();

    void pushRegister(int address, float value);

    std::vector<float> getAllRegisterValue(int address);

    std::vector<float> getAllRegisterValue();

    std::vector<int> getAllRegisterAddress();

    void clearRegisters();

    void defaultClear();

};

#endif // SYSTEMSTATE_H