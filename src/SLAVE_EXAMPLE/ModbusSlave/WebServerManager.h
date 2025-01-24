#ifndef WEBSERVERMANAGER_H
#define WEBSERVERMANAGER_H

#include "ModbusRTUMaster.h"
#include "Utils.h"
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

class WebServerManager {
public:
    WebServerManager(const char *ssid, const char *password, bool &master, bool &swap);
    void begin(ModbusRTUMaster &modbus);
    void handleClient();
    String getSsid();
    String getPassword();
    

private:
    const char *default_ssid;
    const char *default_password;
    String ssid_ap;
    String password_ap;
    WebServer server;
    DNSServer dnsServer; 
    bool &master;
    bool &swap;
    ModbusRTUMaster *modbusMaster;

    void handleRoot();
    void handleWifiConfig();
    void handleDataPage();
    void handleReadRegister();
    void handleAddData();
    void handleDeleteData();
    void handleUpdateData();
    void handleToggleMaster();
    void handleToggleSwap();
};

#endif
