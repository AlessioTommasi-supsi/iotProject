#include "ModbusRTUMaster.h"
#include "ModbusRTUSlave.h"
#include "Utils.h"
#include <HardwareSerial.h>

#define SLAVE_ID 1 
#define RX_PIN_MASTER 16  
#define TX_PIN_MASTER 17
#define DE_PIN_MASTER 15

#define RX_PIN_SLAVE 23
#define TX_PIN_SLAVE 22 //cambiato in origine era 32 da testare se 27 funziona
#define DE_PIN_SLAVE 18 // cambiato in origine era 27 da testare se 27 funziona

const int analogInput_1 = 34;
float mis = 0.0;

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


void fillHoldingRegisters(uint16_t startAddress, uint16_t quantity) {
    

    uint16_t holdingRegistersSlave[20];
    
    // Inizializza i registri da 1 a 10 con il valore 100
    for (uint16_t i = 0; i < 20; i++) {
        if (i >= 1 && i <= 10) {
            holdingRegistersSlave[i] = 100;
        } else {
            holdingRegistersSlave[i] = 5;
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
  modbus.setTimeout(2);//(2000);
  modbus.begin(9600, SERIAL_8N1, RX_PIN_MASTER, TX_PIN_MASTER); 

  modbusSlave.begin(SLAVE_ID, 9600, SERIAL_8N1, RX_PIN_SLAVE, TX_PIN_SLAVE);
  modbusSlave.setFillHoldingRegistersCallback(fillHoldingRegisters);


}

void loop() {
    mis = (analogRead(analogInput_1)*(3.3/4095));

    Serial.println(mis);
    modbusSlave.poll();
  

  unsigned long currentMillisMainLoop = millis();
  if (currentMillisMainLoop - previousMillisMainLoop >= intervalMainLoop) {
    previousMillisMainLoop = currentMillisMainLoop;
  }
}