#ifndef VIEWEDITPIN_H
#define VIEWEDITPIN_H

#include <Arduino.h>
#include "viewGeneric.h"
#include <vector>
#include "SystemState.h"
#include "PinType.h"
#include "Pin.h"

class viewEditPin
{
private:
public:
    static Pin *selectedPin;
    static String html;
    static String generateHTML();
    static String generateForm(int pinNumber);
    static String generateHTML(int pinNumber);
    static String generateHTML(int pinNumber, String script);
    static String addDefaultScript();
    static String addCustomScript(String script);
};

#endif