#ifndef WiFiManager_h
#define WiFiManager_h

#include <WiFi.h>

class WiFiManager
{
private:
    const char *ssid;
    const char *password;

public:
    WiFiManager(const char *ssid, const char *password);
    WiFiManager();
    ~WiFiManager(); // Distruttore
    void connect();
};

#endif