#ifndef LIBRARY_H
#define LIBRARY_H
#include "../model/Library.cpp"
#endif

#include "SystemState.h"

SystemState *SystemState::instance = nullptr;
std::mutex SystemState::mutex;
std::string SystemState::error_message = "";

SystemState *SystemState::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr)
    {
        instance = new SystemState();
        error_message = "";
    }
    return instance;
}

void SystemState::update()
{
    if (ledWrite != nullptr)
    {
        ledWrite->actionOK();
    }
    if (ledSignal != nullptr)
    {
        ledSignal->actionOK();
    }
    
}

void SystemState::setState(State newState)
{
    {
        std::lock_guard<std::mutex> lock(mutex);
        state = newState;
    }
    update();
}

void SystemState::setLedWrite(Led *led)
{
    ledWrite = led;
}

void SystemState::setLedSignal(Led *led)
{
    ledSignal = led;
}

State SystemState::getState()
{
    std::lock_guard<std::mutex> lock(mutex);
    return state;
}

std::string SystemState::getStateString()
{
    std::lock_guard<std::mutex> lock(mutex);
    switch (state)
    {
    case State::INIT:
        return "INIT";
    case State::READ:
        return "READ";
    case State::WRITE:
        return "WRITE";
    case State::DUPLICATE:
        return "DUPLICATE";
    default:
        return "ERROR";
    }
}

void SystemState::setError(std::string message)
{
    {
        std::lock_guard<std::mutex> lock(mutex);
        error_message = message;
    }
    std::cout << "Error occourred: " << message << std::endl;
    setState(State::ERROR);
}

std::string SystemState::getError()
{
    std::lock_guard<std::mutex> lock(mutex);
    return error_message;
}

void SystemState::sendErrorMail()
{
    /*fai partire un nuovo thread che invia una mail con errore in */
}




#ifdef TEST_SYSTEM

void testSystemState1()
{
    SystemState *sys = SystemState::getInstance();
    // sys->setLedWrite(new Led(27)); // Nota: commentato per problemi di dipendenza circolare!

    sys->setState(State::INIT);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    sys->setState(State::READ);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    sys->setState(State::WRITE);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    sys->setState(State::DUPLICATE);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    sys->setState(State::ERROR);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    delete sys;
}

void testSystemState2()
{
    SystemState *system = SystemState::getInstance();

    // Test del sistema
    system->setState(State::WRITE);

    // Esempio di utilizzo dello stato
    if (system->getState() == State::READ)
    {
        std::cout << "Lo stato del sistema è READ" << std::endl;
    }
    else
    {
        std::cout << "Lo stato del sistema non è READ" << std::endl;
    }

    // Deallocazione dell'istanza del sistema
    delete system;
}

int main()
{
    testSystemState1();

    return 0;
}

#endif
