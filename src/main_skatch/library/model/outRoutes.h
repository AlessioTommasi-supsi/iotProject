#ifndef OUTROUTES_H
#define OUTROUTES_H


#include "RoutesInterface.h"
#include <ESPAsyncWebSrv.h>
#include <Arduino.h>
#include <vector>
#include <string>


#include "ADS1115_controller.h"



#include "viewGraph.h"
#include "viewMultiplex.h"

#include "SystemState.h"
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>


class OutRoutes
{
public:
    void defineRoutes(AsyncWebServer &server);
};

#endif