#include "ModbusRTUMaster.h"
#include "DisplayOled.h"
#include "ModbusRTUSlave.h"
#include "Utils.h"
#include "WebServerManager.h"
#include <HardwareSerial.h>

#define SLAVE_ID 1 
#define RX_PIN_MASTER 16  
#define TX_PIN_MASTER 17
#define DE_PIN_MASTER 15

#define RX_PIN_SLAVE 32
#define TX_PIN_SLAVE 33
#define DE_PIN_SLAVE 27

HardwareSerial SerialPort(1); 
bool master = false;
bool swap = false;
bool success = 0;
int indexValuesArray = 0;
unsigned long previousMillisMainLoop = 0; 
unsigned long previousMillisRead = 0;      
const long intervalMainLoop = 1000;        
const long intervalRead = 750; 

ModbusRTUMaster modbus(Serial2, DE_PIN_MASTER);
ModbusRTUSlave modbusSlave(SerialPort, DE_PIN_SLAVE);

WebServerManager webServerManager("CONFIGURE_ME_ESP32_G2", "", master, swap);

void fillHoldingRegisters(uint16_t startAddress, uint16_t quantity) {
    uint16_t holdingRegistersSlave[20];
    
    // Inizializza i registri da 1 a 10 con il valore 100
    for (uint16_t i = 0; i < 20; i++) {
        if (i >= 1 && i <= 10) {
            holdingRegistersSlave[i] = 100;
        } else {
            holdingRegistersSlave[i] = 0;
        }
    }
    

    success = modbus.readHoldingRegisters(SLAVE_ID, startAddress, holdingRegistersSlave, quantity);
    if (success) {
        if (swap) {
            for (int i = 0; i < quantity; i += 2) {
                int temp = holdingRegistersSlave[i];
                holdingRegistersSlave[i] = holdingRegistersSlave[i + 1];
                holdingRegistersSlave[i + 1] = temp;
            }
        }
        modbusSlave.updateHoldingRegistersSlave(holdingRegistersSlave, quantity);
    }
}

void setup() {
  Serial.begin(9600);
  setupDisplay();
  modbus.setTimeout(2000);
  modbus.begin(9600, SERIAL_8N1, RX_PIN_MASTER, TX_PIN_MASTER); 

  modbusSlave.begin(SLAVE_ID, 9600, SERIAL_8N1, RX_PIN_SLAVE, TX_PIN_SLAVE);
  modbusSlave.setFillHoldingRegistersCallback(fillHoldingRegisters);
  webServerManager.begin(modbus);
}

void loop() {
  webServerManager.handleClient();

  if (master) {
    printOnDisplay("Master");
  } else {
    printOnDisplay("Slave");
    Serial.println("Slave");
    modbusSlave.poll();
  }

  unsigned long currentMillisMainLoop = millis();
  if (currentMillisMainLoop - previousMillisMainLoop >= intervalMainLoop) {
    previousMillisMainLoop = currentMillisMainLoop;
  }
}
