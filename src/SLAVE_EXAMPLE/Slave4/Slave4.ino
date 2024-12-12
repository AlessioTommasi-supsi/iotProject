#include "ModbusRTUSlave.h"

#define SLAVE_ID 1
#define RX_PIN_SLAVE 32
#define TX_PIN_SLAVE 33
#define DE_PIN_SLAVE 27

HardwareSerial SerialPort(1);
ModbusRTUSlave modbusSlave(SerialPort, DE_PIN_SLAVE);

uint16_t holdingRegisters[100];

void fillHoldingRegisters(uint16_t startAddress, uint16_t quantity) {
    for (uint16_t i = 0; i < quantity; i++) {
        if (startAddress + i < 100) {
            holdingRegisters[startAddress + i] = 100;
        }
    }
}

void setup() {
    Serial.begin(9600);
    Serial.println("setup slave");
    modbusSlave.begin(SLAVE_ID, 9600, SERIAL_8N1, RX_PIN_SLAVE, TX_PIN_SLAVE);
    modbusSlave.configureHoldingRegisters(holdingRegisters, 100);
    
    modbusSlave.setFillHoldingRegistersCallback(fillHoldingRegisters);
}

void loop() {
    modbusSlave.poll();
    Serial.println("poool");
}
