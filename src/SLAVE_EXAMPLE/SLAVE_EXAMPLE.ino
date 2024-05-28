#include <ModbusRTU.h>

// Crea un'istanza di ModbusRTU
ModbusRTU mb;

// Indirizzo del dispositivo slave
const uint8_t SLAVE_ID = 1;

// Pin di controllo DE/RE per il modulo RS485
const int DE_RE_PIN = 27;  // Modifica questo valore in base al tuo schema

// Variabili che verranno lette tramite Modbus
uint16_t holdingRegister1 = 0;
uint16_t holdingRegister2 = 123;  // Un altro esempio di registro holding
uint16_t holdingRegister100 = 50; // Registro alla posizione 100

void setup() {
  // Inizializza la comunicazione seriale per il debug
  Serial.begin(115200);

  // Inizializza il pin DE/RE
  pinMode(DE_RE_PIN, OUTPUT);
  digitalWrite(DE_RE_PIN, HIGH); // Imposta il pin DE/RE su HIGH per trasmettere (sempre in trasmissione)

  // Inizializza la comunicazione seriale per Modbus
  Serial2.begin(9600, SERIAL_8N1, 26, 25); // UART2, RX=26, TX=25

  // Imposta l'indirizzo del dispositivo slave
  mb.slave(SLAVE_ID);

  // Aggiungi i registri holding
  mb.addHreg(0, holdingRegister1);    // Registro alla posizione 0
  mb.addHreg(1, holdingRegister2);    // Registro alla posizione 1
  mb.addHreg(100, holdingRegister100); // Registro alla posizione 100

  // Inizializza Modbus
  mb.begin(&Serial2);

  // Stampa messaggio di inizializzazione completata
  Serial.println("Modbus RTU Slave Initialized");
}

void loop() {
  // Aggiorna Modbus (gestisce le richieste e le risposte)
  mb.task();

  // Simula un cambiamento nel valore dei registri holding per esempio
  mb.Hreg(0, ++holdingRegister1); // Aggiorna il valore del registro 0
  mb.Hreg(1, --holdingRegister2); // Aggiorna il valore del registro 1
  mb.Hreg(100, holdingRegister100); // Aggiorna il valore del registro 100

  // Tempo di attesa tra un aggiornamento e l'altro
  delay(1000);
}
