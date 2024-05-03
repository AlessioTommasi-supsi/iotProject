#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <ESPAsyncWebServer.h>

class WebServer
{
public:
    WebServer();
    ~WebServer();
    void begin();
    void handleClient();
    void stop();
    void start();

    // Static member function for the task
    static void handleClientTaskFunction(void *parameter);

private:
    AsyncWebServer _server;

    void setupRoutes();
    TaskHandle_t handleClientTask;
};

#endif // WEBSERVER_H