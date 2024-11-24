#include <ModbusRTU.h>

// Definizione dei pin
#define RS485_GPIO_RX 16 // RX2
#define RS485_GPIO_TX 17 // TX2
#define RS485_GPIO_RTS 4 // DE/RE

// Crea un'istanza di ModbusRTU
ModbusRTU mb;

// Funzioni di pre e post trasmissione
void preTransmission() {
  digitalWrite(RS485_GPIO_RTS, HIGH); // Imposta il pin DE/RE su HIGH per trasmettere
}

void postTransmission() {
  digitalWrite(RS485_GPIO_RTS, LOW); // Imposta il pin DE/RE su LOW per ricevere
}

void setup() {
  // Inizializza la comunicazione seriale per il debug
  Serial.begin(115200);

  // Inizializza il pin DE/RE
  pinMode(RS485_GPIO_RTS, OUTPUT);
  digitalWrite(RS485_GPIO_RTS, LOW); // Imposta il pin DE/RE su LOW per ricevere

  // Inizializza la comunicazione seriale per Modbus
  Serial2.begin(9600, SERIAL_8N1, RS485_GPIO_RX, RS485_GPIO_TX); // UART2, RX=16, TX=17

  // Inizializza Modbus communication
  mb.begin(&Serial2, RS485_GPIO_RTS);
  mb.slave(1);
  mb.preTransmission(preTransmission);
  mb.postTransmission(postTransmission);
  Serial.println("Modbus RTU Slave Initialized");

  // Aggiungi i registri holding
  mb.addHreg(1, 100); // Example register with value 100
  mb.addHreg(10, 200); // Another example register
  mb.addHreg(100, 300); // Another example register
}

void loop() {
  // Aggiungi messaggio di debug
  Serial.println("Inizio loop");

  // Aggiorna la comunicazione Modbus
  mb.task();

  // Aggiungi messaggio di debug
  Serial.println("Fine loop");

  delay(1000);
}