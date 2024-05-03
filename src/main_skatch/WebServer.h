#ifndef WebServer_h
#define WebServer_h

#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebSrv.h>

class WebServer
{
private:
    AsyncWebServer server{80};
    const char *ssid;
    const char *password;
    const char *PARAM_MESSAGE = "message";

    void notFound(AsyncWebServerRequest *request);

public:
    WebServer(const char *ssid, const char *password);
    void begin();
};

#endif
