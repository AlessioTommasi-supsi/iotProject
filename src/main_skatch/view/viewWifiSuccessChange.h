#ifndef viewWifiSuccessChange_H
#define viewWifiSuccessChange_H

#include <Arduino.h>
#include "viewGeneric.h"
#include <vector>
#include <set> 
#include "SystemState.h"

class viewWifiSuccessChange
{
private:
public:
    static String html;
    static String generateHTML();
    static String generateHTML( std::string ip_address);

    static String generateContent(std::string ip_address);
};

#endif