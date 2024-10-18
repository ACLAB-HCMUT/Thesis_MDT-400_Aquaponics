#include "convert.h"
float convertToFloat(const std::uint8_t bytes[4]) {
  // Combine the bytes into a single unsigned integer
  unsigned int intValue = (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];

  // Extract sign, exponent, and mantissa
  unsigned int sign = (intValue >> 31) & 1;
  unsigned int exponent = (intValue >> 23) & 0xFF;
  unsigned int mantissa = intValue & 0x7FFFFF;

  // Calculate the floating-point value
  float result = std::ldexp(static_cast<float>(mantissa) / (1 << 23) + 1.0f, exponent - 127);
  if (sign) {
    result = -result;
  }

  return result;
}