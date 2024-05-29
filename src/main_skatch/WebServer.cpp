#include "WebServer.h"
#include "Routes.h"

WebServer::WebServer(const char *ssid, const char *password) : ssid(ssid), password(password) {}

void WebServer::begin()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("WiFi Failed!");
        return;
    }
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "Hello, world"); });

    server.on("/get", HTTP_GET, [this](AsyncWebServerRequest *request)
              {
        String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, GET: " + message); });

    server.on("/post", HTTP_POST, [this](AsyncWebServerRequest *request)
              {
        String message;
        if (request->hasParam(PARAM_MESSAGE, true)) {
            message = request->getParam(PARAM_MESSAGE, true)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, POST: " + message); });

    server.onNotFound([this](AsyncWebServerRequest *request)
                      { this->notFound(request); });
                      
    Routes::defineRoutes(server);
    server.begin();
    Serial.println("Server started");
}

void WebServer::notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}
