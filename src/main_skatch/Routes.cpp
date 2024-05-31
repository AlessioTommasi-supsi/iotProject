#include "Routes.h"


void Routes::defineRoutes(AsyncWebServer &server)
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "Hello, world"); });

    

    /*
    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, GET: " + message); });

    server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        String message;
        if (request->hasParam(PARAM_MESSAGE, true)) {
            message = request->getParam(PARAM_MESSAGE, true)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, POST: " + message); });

    

    */



    server.on("/newroute", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "Hello from new route!"); });

    server.on("/anotherroute", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "Hello from another route!"); });

    server.on("/history", HTTP_GET, [](AsyncWebServerRequest *request){
                String htmlContent = viewHistory::generateHTML();
                const char *htmlContentPtr = htmlContent.c_str();
                request->send(200, "text/html", htmlContentPtr); 
    });

    server.on("/currentregister", HTTP_GET, [](AsyncWebServerRequest *request){
                String htmlContent = viewCurrentRegister::generateHTML();
                const char *htmlContentPtr = htmlContent.c_str();
                request->send(200, "text/html", htmlContentPtr); 
    });

    server.on("/modbusMaster", HTTP_GET, [](AsyncWebServerRequest *request){
                String registerAddress = request->getParam("registerAddress")->value();
                String registerType = request->getParam("registerType")->value();

                if(registerType == "int")
                {
                    float registerValue = SystemState::masterModbus->readHoldingIntRegisters(registerAddress.toInt());
                    String htmlContent = viewCurrentRegister::generateHTML(registerAddress, registerValue);
                    const char *htmlContentPtr = htmlContent.c_str();
                    request->send(200, "text/html", htmlContentPtr); 
                }
                else if(registerType == "float")
                {
                    float registerValue = SystemState::masterModbus->readHoldingFloatRegisters(registerAddress.toInt());
                    String htmlContent = viewCurrentRegister::generateHTML(registerAddress, registerValue);
                    const char *htmlContentPtr = htmlContent.c_str();
                    request->send(200, "text/html", htmlContentPtr); 
                }
                else
                {
                    request->send(400, "text/plain", "Invalid register type");
                }

                String htmlContent = viewCurrentRegister::generateHTML();
                const char *htmlContentPtr = htmlContent.c_str();
                request->send(200, "text/html", htmlContentPtr); 
    });

    server.on("/storevalue", HTTP_GET, [](AsyncWebServerRequest *request){
                String registerValue = request->getParam("registerValue")->value();
                String registerAddress = request->getParam("registerAddress")->value();

                SystemState::getInstance()->pushRegister(registerAddress.toInt(), registerValue.toFloat());

                String htmlContent = viewCurrentRegister::generateHTMLConfirm(registerAddress, registerValue.toFloat());
                const char *htmlContentPtr = htmlContent.c_str();
                request->send(200, "text/html", htmlContentPtr); 
    });

}