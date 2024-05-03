#ifndef WiFiManager_h
#define WiFiManager_h

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>

class WiFiManager
{

public:
    const char *ssid;
    const char *password;
    WiFiManager(const char *ssid, const char *password);
    WiFiManager();
    ~WiFiManager(); // Distruttore
    void connect();
};

#endif