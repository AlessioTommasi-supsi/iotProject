
#include "SystemState.h"


SystemState *SystemState::instance = nullptr;
char * SystemState::error_message = "";


SystemState *SystemState::getInstance()
{
    if (instance == nullptr)
    {
        instance = new SystemState();
        error_message = "";
    }
    return instance;
}

void SystemState::update()
{
    //qui per esempio posso modificare led in base allo stato del componente!
    
}

void SystemState::pushRegister(int addr, float val)
{
    address.push_back(addr);
    value.push_back(val);
}

std::vector<float> SystemState::getAllRegisterValue(int addres)
{
    std::vector<float> values;
    for (int i = 0; i < address.size(); i++)
    {
        if (address[i] == addres)
        {
            values.push_back(value[i]);
        }
    }
    return values;
}

std::vector<int> SystemState::getAllRegisterAddress()
{
    return address;
}

void SystemState::clearRegisters()
{
    address.clear();
    value.clear();
}


void SystemState::setState(State newState)
{
    
    state = newState;
    update();
}

State SystemState::getState()
{    
    return state;
}

char * SystemState::getStateString()
{
    switch (state)
    {
    case State::INIT:
        return "INIT";
    case State::MASTER:
        return "MASTER";
    case State::SLAVE:
        return "SLAVE";
    default:
        return "ERROR";
    }
}

void SystemState::setError(char* message)
{
    
    error_message = message;

    Serial.println("Error occourred!");

    setState(State::ERROR);
}

char * SystemState::getError()
{
    return error_message;
}


