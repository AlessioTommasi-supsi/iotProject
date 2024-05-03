#include "WebServer.h"

WebServer::WebServer() {}

WebServer::~WebServer()
{
    stop();
}

void WebServer::handleClientTaskFunction(void *parameter)
{
    WebServer *webServer = (WebServer *)parameter;
    while (true)
    {
        webServer->handleClient();
        delay(100); // Delay per evitare un loop troppo veloce
    }
}

void WebServer::begin()
{
    setupRoutes();
    _server.begin();
    
    start();
    Serial.println("HTTP server started");
}

void WebServer::handleClient()
{
    _server.handleClient();
}

void WebServer::setupRoutes()
{
    /*
    _server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(200, "text/plain", "Hello, ESP32!"); });
    */
    // Send a GET request to <IP>/get?message=<message>
    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, GET: " + message); });

    // Send a POST request to <IP>/post with a form field message set to <message>
    server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        String message;
        if (request->hasParam(PARAM_MESSAGE, true)) {
            message = request->getParam(PARAM_MESSAGE, true)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, POST: " + message); });
        
}

void WebServer::start(){
    xTaskCreatePinnedToCore(handleClientTaskFunction, "handleClient", 10000, this, 1, &handleClientTask, 1);
}

void WebServer::stop()
{
    vTaskDelete(handleClientTask);
}

