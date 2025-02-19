
#include "MasterModbus.h"


MasterModbus *masterModbus = nullptr;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial)
  {
    ; // Attendi finché la porta seriale non è pronta
  }

  masterModbus = new MasterModbus();

}

void loop() {
  uint16_t addr_integer = 0;
  int value = masterModbus->readHoldingIntRegisters(addr_integer);

  uint16_t addr_float = 1;
  float value_float = masterModbus->readHoldingFloatRegisters(addr_float);

  delay(500);
}
