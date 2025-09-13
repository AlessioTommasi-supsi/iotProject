#ifndef ROUTESINTERFACE_H
#define ROUTESINTERFACE_H

#include <ESPAsyncWebSrv.h>

class RoutesInterface
{
public:
    virtual void defineRoutes(AsyncWebServer &server);
};

#endif // !ROUTESINTERFACE_H


