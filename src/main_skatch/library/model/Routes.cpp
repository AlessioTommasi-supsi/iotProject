#include "Routes.h"


void Routes::defineRoutes(AsyncWebServer &server)
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){ 
        String htmlContent = viewHome::generateHTML();
        //String htmlContent = "Hello World!";
        const char *htmlContentPtr = htmlContent.c_str();
        request->send(200, "text/html", htmlContentPtr); 
    });
    
    
    
    // Nuove rotte per caricamento dinamico dei contenuti frammentati
    server.on("/homePageContent", HTTP_GET, [](AsyncWebServerRequest *request){
        try {
            String content = viewHome::pageContent();
            AsyncWebServerResponse *response = request->beginResponse(200, "text/html", content);
            response->addHeader("Access-Control-Allow-Origin", "*");
            response->addHeader("Cache-Control", "no-cache");
            request->send(response);
        } catch (...) {
            request->send(500, "text/html", "Error loading home content");
        }
    });

   
    

    cssRoutes css;
    css.defineRoutes(server);

    pinoutRoutes pinout;
    pinout.defineRoutes(server);

    ModbusRoutes modbus;
    modbus.defineRoutes(server);

    WifiRoutes wifi;
    wifi.defineRoutes(server);

    MonitorResource monitor;
    monitor.defineRoutes(server);

    MultiplexRoutes multiplex;
    multiplex.defineRoutes(server);

    OutRoutes out;
    out.defineRoutes(server);

    

}