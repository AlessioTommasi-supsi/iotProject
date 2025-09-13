#include "Utils.h"

float convertToFloat(uint16_t register1, uint16_t register2) {
  uint32_t combinedValue = (static_cast<uint32_t>(register1) << 16) | register2;
  uint32_t sign = (combinedValue >> 31) & 0x01;
  int32_t exponent = ((combinedValue >> 23) & 0xFF) - 127;
  uint32_t mantissa = combinedValue & 0x7FFFFF;
  float result = pow(-1, sign) * (1 + (mantissa / pow(2, 23))) * pow(2, exponent);

  return result;
}

void convertToRegisters(float data, uint16_t &register1, uint16_t &register2) {
    // Convert the float into a uint32_t bit representation
    uint32_t raw;
    std::memcpy(&raw, &data, sizeof(raw));  // Copy the float's bits to raw

    // Extract the sign, exponent, and mantissa
    uint32_t sign = (raw >> 31) & 0x01;
    uint32_t exponent = (raw >> 23) & 0xFF;
    uint32_t mantissa = raw & 0x7FFFFF;

    // Combine sign, exponent, and mantissa back into two 16-bit registers
    register1 = (exponent << 7) | (mantissa >> 16);  // High word
    register2 = mantissa & 0xFFFF;  // Low word
}
