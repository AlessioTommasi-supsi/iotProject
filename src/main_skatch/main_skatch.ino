#include <Arduino.h>
#include "WebServer.h"
#include "MasterModbus.h"
#include "SlaveModbus.h"


const char *ssid = "HomeInternet";
const char *password = "occhioallapennachecade";
WebServer webServer(ssid, password);

// Modbus slave configuration
#define SLAVE_ID 1
#define SLAVE_SERIAL Serial2 // Serial port for Modbus communication with slave
#define SLAVE_BAUDRATE 9600

// Modbus master configuration
#define MASTER_SERIAL Serial // Serial port for Modbus communication with master
#define MASTER_BAUDRATE 9600

#define DATA_LENGTH 8 // Lunghezza dei dati letti dal master

#define ESP32_RX_PIN 4 // RX pin del ESP32
#define ESP32_TX_PIN 5 // TX pin del ESP32


SlaveModbus slaveModbus(SLAVE_ID);
MasterModbus masterModbus;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    ; // Attendi finché la porta seriale non è pronta a
  }

  Serial.println("La porta seriale è pronta! Hello, world!");

  webServer.begin();
  slaveModbus.begin(Serial);  // Initialize Modbus slave
  masterModbus.begin(Serial); // Initialize Modbus master

  delay(50000);

  destroy();
}

void destroy()
{
}

void loop()
{
  // Esegui le operazioni del master Modbus
  // In questo esempio, leggiamo i coil dallo slave
  bool coils[DATA_LENGTH];
  masterModbus.readCoils(SLAVE_ID, 1, coils, DATA_LENGTH);

  // Esegui le operazioni del slave Modbus
  // In questo esempio, controlliamo i valori dei holding register
  slaveModbus.setHoldingRegisterValue(1, 100);
  slaveModbus.task();
  yield();
  // Aggiungi eventuali altre operazioni qui...

  delay(1000); // Delay di 1 secondo prima di eseguire il loop successivo
}