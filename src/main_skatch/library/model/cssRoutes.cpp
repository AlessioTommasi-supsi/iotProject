#include "cssRoutes.h"


void cssRoutes::defineRoutes(AsyncWebServer &server)
{
    server.on("/style", HTTP_GET, [](AsyncWebServerRequest *request){
        String css = viewGeneric::addCss();
        // Prepara la risposta includendo gli header e il contenuto
        AsyncWebServerResponse *response = request->beginResponse(200, "text/html", css);
        response->addHeader("Access-Control-Allow-Origin", "*"); // Aggiungi header CORS
        request->send(response); 
    });
    
    server.on("/formStyle", HTTP_GET, [](AsyncWebServerRequest *request){
        String css = viewGeneric::addFormStyleCss();
        AsyncWebServerResponse *response = request->beginResponse(200, "text/html", css);
        response->addHeader("Access-Control-Allow-Origin", "*"); // Aggiungi header CORS
        request->send(response); 
    });

    server.on("/fieldFormStyle", HTTP_GET, [](AsyncWebServerRequest *request){
        String css = viewGeneric::addFieldFormStyleCss();
        AsyncWebServerResponse *response = request->beginResponse(200, "text/html", css);
        response->addHeader("Access-Control-Allow-Origin", "*"); // Aggiungi header CORS
        request->send(response); 
    });
    
    server.on("/pinStyle", HTTP_GET, [](AsyncWebServerRequest *request){
        String css = viewGeneric::addPinStyleCss();
        AsyncWebServerResponse *response = request->beginResponse(200, "text/html", css);
        response->addHeader("Access-Control-Allow-Origin", "*"); // Aggiungi header CORS
        request->send(response); 
    });
    
    server.on("/navbarStyle", HTTP_GET, [](AsyncWebServerRequest *request){
        String css = viewGeneric::addNavbarStyleCss();
        AsyncWebServerResponse *response = request->beginResponse(200, "text/html", css);
        response->addHeader("Access-Control-Allow-Origin", "*"); // Aggiungi header CORS
        request->send(response); 
    });
    
}