#include <Arduino.h>
#include "LedEsp32.h"
#include "WebServer.h"

LedEsp32 *led;

const char *ssid = "HomeInternet";
const char *password = "occhioallapennachecade";

WebServer webServer(ssid, password);

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    ; // Attendi finché la porta seriale non è pronta
  }

  Serial.println("La porta seriale è pronta! Hello, world!");

  led = new LedEsp32(13);
  webServer.begin();

  led->blink(1);
  delay(50000);

  destroy();
}

void destroy()
{
  // Deallocazione de
  delete led;
}

void loop()
{
  //server.handleClient();
}