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
bool swap = true;
bool success = 0;
int indexValuesArray = 0;
unsigned long previousMillisMainLoop = 0; 
unsigned long previousMillisRead = 0;      
const long intervalMainLoop = 1000;        
const long intervalRead = 750; 

ModbusRTUMaster modbus(Serial2, DE_PIN_MASTER);
ModbusRTUSlave modbusSlave(SerialPort, DE_PIN_SLAVE);

/**
 * Al massimo si possono selezionare 20 registri!
 * 
 * come funziona: 
 * 
 * vede che registro di partenza sta richedendo modscan
 * e invia in base all indirizzo di partenza che e stato selezionato!
 * 
 * tutto questo e fatto nella funzione _processReadHoldingRegisters
 */


void fillHoldingRegisters(uint16_t startAddress, uint16_t quantity) {    
    
   Serial.print("callbak eseguita");
}

void setup() {
  Serial.begin(9600);
  modbus.setTimeout(2);//(2000);
  modbus.begin(9600, SERIAL_8N1, RX_PIN_MASTER, TX_PIN_MASTER); 

  modbusSlave.begin(SLAVE_ID, 9600, SERIAL_8N1, RX_PIN_SLAVE, TX_PIN_SLAVE);
  modbusSlave.setFillHoldingRegistersCallback(fillHoldingRegisters);

}

void loop() {
   
    modbusSlave.poll();

    /**
     * PER ALESSIO IN QUESTO PUNTO VIENE ESEGUITA LA FUNZIONE CHE RESTITUISCE A 
     * MODSCAN I VALORI 3.2 FLOAT E 1 INTEGER
     *  
     * */ 
  modbusSlave.insertIntoHoldingRegistersSlave(3, 3.2, swap);
  modbusSlave.insertIntoHoldingRegistersSlave(5, 1, false);
    

  unsigned long currentMillisMainLoop = millis();
  if (currentMillisMainLoop - previousMillisMainLoop >= intervalMainLoop) {
    previousMillisMainLoop = currentMillisMainLoop;
  }
}