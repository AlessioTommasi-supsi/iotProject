#include "Routes.h"


void Routes::defineRoutes(AsyncWebServer &server)
{
    server.on("/newroute", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "Hello from new route!"); });

    server.on("/anotherroute", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "Hello from another route!"); });

    server.on("/currentregister", HTTP_GET, [](AsyncWebServerRequest *request){
                String htmlContent = viewCurrentRegister::generateHTML();
                const char *htmlContentPtr = htmlContent.c_str();
                request->send(200, "text/html", htmlContentPtr); 
    });
}