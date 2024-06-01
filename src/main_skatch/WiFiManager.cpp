#include "WiFiManager.h"

#include "WebServer.h"

WebServer *my_webServer = nullptr;

WiFiManager::WiFiManager()
{
    this->ssid = "HomeInternet";
    this->password = "occhioallapennachecade";
    this->connect();
}

WiFiManager::WiFiManager(const char *ssid, const char *password)
{
    this->ssid = ssid;
    this->password = password;
    this->connect();
}

void WiFiManager::connect()
{
    if (my_webServer != nullptr)
    {
        //delete my_webServer;
        my_webServer = nullptr;
    }
    try
    {
        WiFi.mode(WIFI_STA);
        WiFi.disconnect(); // Disconnetti eventuali connessioni pregresse

        delay(100);

        Serial.println("Connessione alla rete Wi-Fi...");

        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            Serial.println("Connessione in corso...");
        }

        my_webServer = new WebServer(ssid, password);
        my_webServer->begin();

        Serial.println("Connessione Wi-Fi stabilita!");
        Serial.print("Indirizzo IP: ");
        Serial.println(WiFi.localIP());
    }
    catch(const std::exception& e)
    {
        Serial.println("Errore durante la connessione alla rete Wi-Fi!");
        throw new std::runtime_error("Errore durante la connessione alla rete Wi-Fi!");
    }
    
    
}


std::vector<std::string> WiFiManager::scanNetworks()
{
    std::vector<std::string> networks;
    int n = WiFi.scanNetworks();
    for (int i = 0; i < n; ++i)
    {
        networks.push_back(std::string(WiFi.SSID(i).c_str()));
        Serial.println(WiFi.SSID(i));
        Serial.println("potenza segnale: "+String(WiFi.RSSI(i)));
    }
    return networks;
}

void WiFiManager::setNetwork(const char *ssid_new, const char *password_new)
{
    const char * old_ssid = this->ssid;
    const char * old_password = this->password;

    this->ssid = ssid_new;
    this->password = password_new;
    try
    {
        this->connect();
    }
    catch(const std::exception& e) //se qualcosa e andato storto ripristino i vecchi valori
    {
        this->setNetwork(old_ssid, old_password);
        Serial.println("Errore durante la connessione alla Nuova rete Wi-Fi!");
        throw new std::runtime_error("Errore durante la connessione alla rete Wi-Fi!");
    }
    
}


WiFiManager::~WiFiManager()
{
    // Distruttore: Dealloca la memoria
    if (my_webServer != nullptr)
    {
        delete my_webServer;
        my_webServer = nullptr;
    }
    Serial.println("Oggetto WiFiManager distrutto, liberazione della memoria...");
}