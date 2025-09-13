#ifndef CSSROUTES_H
#define CSSROUTES_H

#include "RoutesInterface.h"
#include <ESPAsyncWebSrv.h>


#include "viewGeneric.h"

class cssRoutes : public RoutesInterface
{
public:
    void defineRoutes(AsyncWebServer &server);
};

#endif // CSSROUTES_H