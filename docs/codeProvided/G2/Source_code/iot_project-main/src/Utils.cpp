#include "Utils.h"

float convertToFloat(uint16_t register1, uint16_t register2) {
  uint32_t combinedValue = (static_cast<uint32_t>(register1) << 16) | register2;
  uint32_t sign = (combinedValue >> 31) & 0x01;
  int32_t exponent = ((combinedValue >> 23) & 0xFF) - 127;
  uint32_t mantissa = combinedValue & 0x7FFFFF;
  float result = pow(-1, sign) * (1 + (mantissa / pow(2, 23))) * pow(2, exponent);

  return result;
}