
#ifndef WIFIROUTES_H
#define WIFIROUTES_H

#include <ESPAsyncWebSrv.h>
#include <Arduino.h>


#include "RoutesInterface.h"

#include "viewConfig.h"
#include "viewWifiSuccessChange.h"

#include "SystemState.h"

class WifiRoutes : public RoutesInterface
{
public:
    void defineRoutes(AsyncWebServer &server);
};

#endif // WIFIROUTES_H