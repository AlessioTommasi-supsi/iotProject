#include <ModbusRTU.h>

#define TX_PIN 17        // Pin TX dell'ESP32
#define RX_PIN 16        // Pin RX dell'ESP32
#define DE_RE_PIN 4      // Pin per controllare DE e RE del modulo RS485

// Oggetto Modbus
ModbusRTU mb;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // Aspetta l'inizializzazione della seriale
  }
  
  Serial.println("porta seriale avviata");

  // Configurazione del pin DE/RE per controllare il driver RS485
  pinMode(DE_RE_PIN, OUTPUT);
  digitalWrite(DE_RE_PIN, LOW); // Imposta DE/RE su ricezione di default

  // Inizializza Serial2 per RS485
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  // Configura Modbus come slave con ID 1
  mb.begin(&Serial2, DE_RE_PIN);
  mb.slave(1);

  // Aggiungi registri Modbus
  mb.addHreg(1, 100); // Registro Holding Register 1 con valore iniziale 100
  mb.addHreg(2, 200); // Registro Holding Register 2 con valore iniziale 200
  mb.addHreg(3, 300); // Registro Holding Register 3 con valore iniziale 300
  Serial.print("Registro 1: ");
  Serial.println(mb.Hreg(1));
  Serial.print("Registro 10: ");
  Serial.println(mb.Hreg(10));
  Serial.print("Registro 100: ");
  Serial.println(mb.Hreg(100));
  Serial.println("Modbus slave avviato");
}

void loop() {
  // Esegui il task Modbus
  mb.task();
  delay(10);
}
