
#include "SystemState.h"
#include "WiFiManager.h"

SystemState *SystemState::instance = nullptr;
MasterModbus *SystemState::masterModbus = nullptr;
bool SystemState::isStopped = false;
WiFiManager *SystemState::wifiManager = nullptr;


char * SystemState::error_message = "";


SystemState::~SystemState()
{
    defaultClear();
}

void SystemState::defaultClear()
{
    delete instance;
    delete masterModbus;
    instance = nullptr;
    masterModbus = nullptr;
}

SystemState *SystemState::getInstance()
{
    if (instance == nullptr)
    {
        instance = new SystemState();
        masterModbus = new MasterModbus();
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

std::vector<float> SystemState::getAllRegisterValue()
{
    return value;
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


void SystemState::setWifiManager(WiFiManager *wifiController)
{
    wifiManager = wifiController;
}


void SystemState::switchNetwork(const char *ssid, const char *password)
{
    setState(State::WIFI_CHANGE);
    wifiManager->setNetwork(ssid, password);
}


void SystemState::deleteValue(int index)
{
    address.erase(address.begin() + index);
    value.erase(value.begin() + index);
}

void SystemState::editValue(int index, float value)
{
    this->value[index] = value;
}