#ifndef WiFiManager_h
#define WiFiManager_h

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>

//#include "WebServer.h"

#include <ESPAsyncWebSrv.h>
#include "SystemState.h"
#include <string>
#include <vector>

class WebServer;

class WiFiManager
{

public:
    const char *ssid;
    const char *password;

    WebServer *my_webServer;

    WiFiManager(const char *ssid, const char *password);
    WiFiManager();
    ~WiFiManager(); // Distruttore
    void connect();
    
    void setNetwork(const char *ssid, const char *password);

    std::vector<std::string> scanNetworks();
};

#endif