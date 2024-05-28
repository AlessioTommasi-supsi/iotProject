#include <ModbusRTUMaster.h> 
 
const uint8_t rxPin = 16; 
const uint8_t txPin = 17; 
const uint8_t dePin = 4; 
 
ModbusRTUMaster modbus(Serial1, dePin); // serial port, driver enable pin for rs-485 (optional) 
 
void processError() { 
  if (modbus.getTimeoutFlag()) { 
    Serial.println(F("Connection timed out")); 
    modbus.clearTimeoutFlag(); 
  } 
  else if (modbus.getExceptionResponse() != 0) { 
    Serial.print(F("Received exception response: ")); 
    Serial.print(modbus.getExceptionResponse()); 
    switch (modbus.getExceptionResponse()) { 
      case 1: 
        Serial.println(F(" - Illegal function")); 
        break; 
      case 2: 
        Serial.println(F(" - Illegal data address")); 
        break; 
      case 3: 
        Serial.println(F(" - Illegal data value")); 
        break; 
      case 4: 
        Serial.println(F(" - Server device failure")); 
        break; 
      default: 
        Serial.println(); 
        break; 
    } 
    modbus.clearExceptionResponse(); 
  } 
  else { 
    Serial.println("An error occurred"); 
  } 
} 
 
 
void setup() { 
  Serial.begin(9600); 
  Serial.setTimeout(100); 
  while(!Serial) {} 
   
  modbus.begin(9600, SERIAL_8N1, rxPin, txPin, false);  
  modbus.setTimeout(100); 
  Serial.print(F("Modbus serial port configuration: 9600")); 
  Serial.println(F("-8-N-1")); 
  Serial.println(); 
} 
 
void loop() {  
  
  uint16_t holdingRegisters[2]; 
  uint16_t address = 122; 
  uint8_t success = modbus.readHoldingRegisters(1, address-1, holdingRegisters, 2);  
  if (success) { 
    // Combine the two 16-bit registers into a 32-bit integer 
    uint32_t combined = ((uint32_t)holdingRegisters[0] << 16) | holdingRegisters[1]; 
    // Convert the combined 32-bit integer to a float 
    float voltage; 
    memcpy(&voltage, &combined, sizeof(voltage)); 
     
    Serial.print(F("Read value of ")); 
    Serial.print(voltage, 6); 
    Serial.print(F(" from holding register address ")); 
    Serial.println(address); 
  } 
  else processError(); 
   
  uint16_t holdingRegister; 
  uint16_t address2 = 500; 
  uint8_t success2 = modbus.readHoldingRegisters(1, address2-1, &holdingRegister, 1);  
  if (success2) { 
    Serial.print(F("Read value of ")); 
    Serial.print(holdingRegister); 
    Serial.print(F(" from holding register address ")); 
    Serial.println(address2); 
  } 
  else processError(); 
 
  delay(500); 
       
}
