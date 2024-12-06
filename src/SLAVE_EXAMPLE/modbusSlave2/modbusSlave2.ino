#include <ModbusRTU.h>

#define TX_PIN 32
#define RX_PIN 33
#define DE_RE_PIN 27

ModbusRTU mb;

bool cbWrite(Modbus::ResultCode event, uint16_t transactionId, void* data) {
  Serial.println("Callback cbWrite");
  return true; // Puoi personalizzare questa logica
}

void setup() {
  // Configurazione della seriale per messaggi di debug a 115200 baud
  Serial.begin(115200);
  while (!Serial); // Attesa per la configurazione della seriale

  Serial.println("Configurazione Modbus RTU slave");

  // Configurazione della seriale per Modbus RTU a 9600 baud
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  mb.begin(&Serial2, DE_RE_PIN);

  Serial.println("Pin configurati:");
  Serial.println("TX_PIN: 32");
  Serial.println("RX_PIN: 33");
  Serial.println("DE_RE_PIN: 27");

  // Aggiungi 5 registri con il valore 100
  for (uint16_t i = 0; i < 5; i++) {
    mb.addHreg(i, 100);
    Serial.print("Registro ");
    Serial.print(i);
    Serial.println(" impostato a 100");
  }

  // Utilizzare la funzione di callback corretta per onSetHreg
  mb.onSetHreg(0, cbWrite, 5); // Offset 0, callback cbWrite, 5 registri
}

void loop() {
  mb.task();
  delay(10);
}
