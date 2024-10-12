#include "WiFiManager.h"

#include "WebServer.h"

WebServer *my_webServer = nullptr;

WiFiManager::WiFiManager()
{
    /*qui creo Esp32 funziona come AP!*/
    this->ssid = "ESP32-Access-Point";
    this->password = "123456789";
    this->setupAP();
}

void WiFiManager::setupAP()
{
    clear_var();
    try
    {
       
        WiFi.mode(WIFI_AP);
        delay(100);
        WiFi.softAP(ssid, password);
        IPAddress IP = WiFi.softAPIP();
        Serial.print("ESP32 AP IP address: ");
        Serial.println(IP);

        this->ip_address = std::string(WiFi.localIP().toString().c_str());

        my_webServer = new WebServer(ssid, password);
        my_webServer->begin();
    }
    catch(const std::exception& e)
    {
        Serial.println("Errore durante la creazione dell'access point!");
    }
    
}

void WiFiManager::clear_var()
{
    if (my_webServer != nullptr)
    {
        try
        {
            if (!isFirstStart)
            {
                delete my_webServer; // da errore di double free soprattutto all avvio non riesco a catturarlo con eccezzione.
            }
                       
        }
        catch (const std::exception &e)
        {
            Serial.println("Errore durante la distruzione del web server!");
        }
        my_webServer = nullptr;
    }
    WiFi.disconnect(); // Disconnetti eventuali connessioni pregresse
}


WiFiManager::WiFiManager(const char *ssid, const char *password)
{
    this->ssid = ssid;
    this->password = password;
    this->connect();
}

void WiFiManager::connect()
{
   clear_var();

    try
    {
        WiFi.mode(WIFI_STA);
        
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
        //this->ip_address = WiFi.localIP().toString();
        this->ip_address = std::string(WiFi.localIP().toString().c_str());
    

    }
    catch(const std::exception& e)
    {
        Serial.println("Errore durante la connessione alla rete Wi-Fi!");
        //throw new std::runtime_error("Errore durante la connessione alla rete Wi-Fi!");
    }
    
    
}

void WiFiManager::smoothConnect() //nota ce ancora errore quando sbaglio a inserire password!
{
    try
    {
        //WiFi.mode(WIFI_STA);
        
        delay(100);

        Serial.println("Connessione alla rete Wi-Fi...");

        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            Serial.println("Connessione in corso...");
        }

        
        Serial.println("smooth Connessione Wi-Fi stabilita!");
        Serial.print("Indirizzo IP: ");
        Serial.println(WiFi.localIP());
        this->ip_address = std::string(WiFi.localIP().toString().c_str());
        Serial.println("ip_address: ");
        Serial.println(this->ip_address.c_str());
    }
    catch(const std::exception& e)
    {
        Serial.println("Errore durante la connessione alla rete Wi-Fi!");
        //throw new std::runtime_error("Errore durante la connessione alla rete Wi-Fi!");
    }
    //return std::string(WiFi.localIP().toString().c_str());
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
        this->smoothConnect();
        isFirstStart = false;
    }
    catch(const std::exception& e) //se qualcosa e andato storto ripristino i vecchi valori
    {
        Serial.println("Errore durante la connessione alla Nuova rete Wi-Fi!");
        this->setNetwork(old_ssid, old_password);
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