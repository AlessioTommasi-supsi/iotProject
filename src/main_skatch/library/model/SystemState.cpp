#include "SystemState.h"
#include "WiFiManager.h"

#include "esp_task_wdt.h"


SystemState *SystemState::instance = nullptr;
MasterModbus *SystemState::masterModbus = nullptr;
bool SystemState::isStopped = false;
WiFiManager *SystemState::wifiManager = nullptr;
PinoutData *SystemState::pinoutData = nullptr;

int SystemState::sd_pin = 0;


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
        sd_pin = 5;
        
        // Inizializza il Logger e la scheda SD
        //Logger::getInstance().begin(sd_pin);

        
    }
    return instance;
}

void SystemState::update()
{
    //qui per esempio posso modificare led in base allo stato del componente!
    //logCurrentState();
    //Serial.println("Updating system state...");
}

void SystemState::logCurrentState() {
    Logger::getInstance().log(String(getStateString()) + " " + String(error_message) + "\n");
}

void SystemState::pushRegister(int addr, float val)
{
    address.push_back(addr);
    value.push_back(val);
}

void SystemState::startRecordingRegister(int addr, int milliseconds)
{
    try
    {
        if (milliseconds < 1000)
        {
            milliseconds = 1000; // Imposta un minimo di 1 secondo per non sovraccaricare il sistema
        }
        
        // Se c'è già una registrazione in corso per questo indirizzo, fermala prima di iniziarne una nuova
        if (recordingActive[addr].load()) {
            stopRecordingRegister(addr);
        }

        recordingActive[addr].store(true);

        recordingThreads[addr] = std::thread([this, addr, milliseconds]() {
            while (recordingActive[addr].load()) {
                int val = SystemState::masterModbus->readHoldingIntRegisters(addr);
                SystemState::getInstance()->pushRegister(addr, val);
                //stampo su seriale notifica
                Serial.println("Recording value: " + String(val) + " at address " + String(addr));

                // Utilizza vTaskDelay per cedere il controllo al sistema operativo
                vTaskDelay(milliseconds / portTICK_PERIOD_MS);
            }
        });
    }
    catch(const std::exception& e)
    {
        stopRecordingRegister(addr);
        setError(("Error: " + String(e.what())).c_str());
    }
}

void SystemState::stopRecordingRegister(int addr)
{
    if (recordingActive[addr].load()) {
        recordingActive[addr].store(false);
        if (recordingThreads[addr].joinable()) {
            recordingThreads[addr].join();
        }
        recordingThreads.erase(addr);
        recordingActive.erase(addr);
    }
}


std::vector<float> SystemState::getAllRegisterValue(int addres)
{
    std::vector<float> values;
    try
    {
        for (int i = 0; i < address.size(); i++)
        {
            if (address[i] == addres)
            {
                values.push_back(value[i]);
            }
        }
    }
    catch(...)
    {
        Serial.println("Error during get all register value");
    }
    
    return values;
}

std::vector<float> SystemState::getAllRegisterValue()
{
    std::vector<float> values;
    try
    {
        for (size_t  i = 0; i < address.size(); i++)
        {
            values.push_back(value[i]);
        }
    }
    catch(...)
    {
        Serial.println("Error during get all register value");
    }
        
    return values;
}

std::vector<int> SystemState::getAllRegisterAddress()
{
    std::vector<int> addreses;
    try
    {
        for (size_t  i = 0; i < address.size(); i++)
        {
            addreses.push_back(address[i]);
        }
    }
    catch(...)
    {
        Serial.println("Error during get all register value");
    }

    return addreses;
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


void SystemState::setPinoutData(PinoutData *pinout)
{
    pinoutData = pinout;

    if (masterModbus != nullptr)
    {
        masterModbus->registerPins(pinoutData);
    }
    
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

void SystemState::setError(const char * message)
{
    char error[100];
    strncpy(error, message, sizeof(error) - 1);
    error[sizeof(error) - 1] = '\0';
    setError(error);
}


void SystemState::setError( char* message)
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
    if (index >= 0 && index < address.size())
    {
        address.erase(address.begin() + index);
        value.erase(value.begin() + index);
    }
}

void SystemState::editValue(int index, float value)
{   
    if (index >= 0 && index < this->value.size())
    {
        this->value[index] = value;
    }
}