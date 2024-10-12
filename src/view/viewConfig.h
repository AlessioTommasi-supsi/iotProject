#ifndef VIEWCONFIG_H
#define VIEWCONFIG_H

#include <Arduino.h>
#include "viewGeneric.h"
#include <vector>
#include <string>
//#include "SystemState.h"

class viewConfig
{
private:
public:
    static String html;
    static String generateHTML();
    static String generateHTML( std::vector<std::string> ssidList);

    static String generateListComponents(std::vector<std::string> &networks);
};

#endif