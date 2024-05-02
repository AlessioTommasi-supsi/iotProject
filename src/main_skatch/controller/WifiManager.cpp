#include "WiFiManager.h"

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
    try
    {
        Serial.println("Connessione alla rete Wi-Fi...");

        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            Serial.println("Connessione in corso...");
        }

        Serial.println("Connessione Wi-Fi stabilita!");
        Serial.print("Indirizzo IP: ");
        Serial.println(WiFi.localIP());
    }
    catch(const std::exception& e)
    {
        Serial.println("Errore durante la connessione alla rete Wi-Fi!");
    }
    
    
}

WiFiManager::~WiFiManager()
{
    // Distruttore: Dealloca la memoria
    Serial.println("Oggetto WiFiManager distrutto, liberazione della memoria...");
}