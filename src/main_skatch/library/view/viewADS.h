#ifndef VIEW_ADS_H
#define VIEW_ADS_H

#include <Arduino.h>
#include "viewGeneric.h"
#include <vector>
#include "ADS1115_controller.h"

class viewADS
{
private:
    /* data */
public:
    static String html;
    static String generateHTML();
    static String adsContent();
};

#endif