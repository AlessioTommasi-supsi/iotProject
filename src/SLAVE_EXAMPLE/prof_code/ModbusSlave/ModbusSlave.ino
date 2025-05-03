#include "ModbusRTUMaster.h"
#include "ModbusRTUSlave.h"
#include "Utils.h"
#include <HardwareSerial.h>

#define SLAVE_ID 1 


/*
ESP32
              +--------+
              |        |
    TX (GPIO22) --------> [DI] RS485 Module
              |        | 
    RX (GPIO23) <-------- [RO] RS485 Module
              |        |
   DE (GPIO18) --------> [DE] (e [RE] se collegati insieme)
              |        |
             GND ------> GND del RS485 Module
              |        |
              +--------+
                
[RS485 Module]    --->   Bus RS485: Terminali A e B <--- (Terminazione e biasing se necessari
*/

#define RX_PIN_SLAVE 22 //DI = tx
#define TX_PIN_SLAVE 23 //RO = rx
#define DE_PIN_SLAVE 18 // DE RE
/*
// scheda!
#define RX_PIN_SLAVE 32 //DI = rx
#define TX_PIN_SLAVE 33 //RO = tx
#define DE_PIN_SLAVE 27 // DE RE
*/


HardwareSerial SerialPort(2);   //utilizza UART1
bool swap = true;
unsigned long previousMillisMainLoop = 0;       
const long intervalMainLoop = 1000;        
const long intervalRead = 750; 

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
  Serial.begin(9600); //utilizza UART0
  modbusSlave.begin(SLAVE_ID, 9600, SERIAL_8N1, RX_PIN_SLAVE, TX_PIN_SLAVE);
  modbusSlave.setFillHoldingRegistersCallback(fillHoldingRegisters);

  Serial.println("inizializzazione fatta!");

}

void loop() {
   
    modbusSlave.poll();

    /**
     * TODO 
     * -fix multiplexer -> per i canali fatto manca vedere effettivamente conversione resistenza etc!
     * -associare ad ohni lettura un indirizzo modbus da 100 a 200
     * - associare equivalente da 200 a 300-> linearizzazione!
     * - scrittura modbus slave
     * - uscite analogiche digitali
     * - prendere da master e replicare sullo slave
     * export XDG_RUNTIME_DIR=/run/user/$(id -u)
     * PER ALESSIO IN QUESTO PUNTO VIENE ESEGUITA LA FUNZIONE CHE RESTITUISCE A 
     * MODSCAN I VALORI 3.2 FLOAT E 1 INTEGER
     *  
     * 
     * mappa ad 
     * 100 -> 200 grandezze misurate   -> come da 200 a 300  ma valori reali letti
     * 200 -> 300 grandezze modificate -> elaborate in base a scale etc  
     * 
     * 200 - 201 - inizio e fine scala  -> 5bar   100bar ->implementa la lettura dallo slave!! comando di openModscan-> 
     * 
     * writeHoldingRegister
     * 
     * 300 -400  VALORI LETTI DA MODSCAN MASTER REPLICATI QUI! SEMPRE REPLICATI 
     * 
     *   REGISTER  address di mastermodbas diventa startaffress e length diventa quantity da mettere -> leggo sempre o 50 int o 50 float!
     * */ 
  modbusSlave.insertIntoHoldingRegistersSlave(3, 3.2, swap);
  modbusSlave.insertIntoHoldingRegistersSlave(5, 1, false);
  //Serial.print("Pool");

  unsigned long currentMillisMainLoop = millis();
  if (currentMillisMainLoop - previousMillisMainLoop >= intervalMainLoop) {
    previousMillisMainLoop = currentMillisMainLoop;
  }
}