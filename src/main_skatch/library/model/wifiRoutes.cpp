#include "wifiRoutes.h"

void WifiRoutes::defineRoutes(AsyncWebServer &server)
{
    
    server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request){
        //String htmlContent = viewGraph::generateHTMLData();
        //const char *htmlContentPtr = htmlContent.c_str();
        //qui devo modificare stato di systemState
        String htmlContent = viewConfig::generateHTML(SystemState::getInstance()->wifiManager->scanNetworks());
        const char *htmlContentPtr = htmlContent.c_str();
        request->send(200, "text/html", htmlContentPtr);
         
    });

    server.on("/switch_wifi", HTTP_GET, [](AsyncWebServerRequest *request){
            String ssid_new = request->getParam("ssid")->value();
            String password_new = request->getParam("password")->value();
            try
            {

                SystemState::getInstance()->switchNetwork(ssid_new.c_str(), password_new.c_str());
                //delay(1000);
                String htmlContent = viewWifiSuccessChange::generateHTML(SystemState::getInstance()->wifiManager->ip_address);
                const char *htmlContentPtr = htmlContent.c_str();
                request->send(200, "text/html", htmlContentPtr);
                 
                //request->send(200, "text/html", "success Switch wifi page");
            }
            catch(...)
            {
                String htmlContent = viewWifiSuccessChange::generateErrorPage(SystemState::getInstance()->wifiManager->ssid, SystemState::getInstance()->wifiManager->ip_address);
                const char *htmlContentPtr = htmlContent.c_str();
                request->send(500, "text/html", htmlContentPtr);

                //request->send(500, "text/html", "error Switch wifi page");
            }
            
    });
}