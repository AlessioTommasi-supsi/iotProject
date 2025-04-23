#ifndef UTILS_H
#define UTILS_H

#include <cstdint>  // For uint16_t, uint32_t
#include <cmath>    // For pow
#include <cstring>  // For std::memcpy

// Function to convert two 16-bit registers to a single float
float convertToFloat(uint16_t register1, uint16_t register2);

// Function to convert a float to two 16-bit registers (high word and low word)
void convertToRegisters(float data, uint16_t &register1, uint16_t &register2);

#endif // UTILS_H
