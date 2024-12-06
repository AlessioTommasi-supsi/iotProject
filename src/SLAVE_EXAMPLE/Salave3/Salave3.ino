#include <ModbusRTU.h>

#define TX_PIN 17
#define RX_PIN 16
#define DE_RE_PIN 4

#define REG_COUNT 10
#define SLAVE_ID 1

ModbusRTU mb;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  mb.begin(&Serial2, DE_RE_PIN);
  mb.slave(SLAVE_ID);

  // Aggiungi 10 registri e impostali a 100
  for (uint16_t i = 0; i < REG_COUNT; i++) {
    mb.addHreg(i, 100);
    Serial.print("Registro ");
    Serial.print(i);
    Serial.println(" impostato a 100");
  }

  Serial.println("Configurazione Modbus RTU slave");
  Serial.println("Pin configurati:");
  Serial.println("TX_PIN: 17");
  Serial.println("RX_PIN: 16");
  Serial.println("DE_RE_PIN: 4");
}

void loop() {
  Serial.println("LOOP");
  mb.task();
  yield();
}
