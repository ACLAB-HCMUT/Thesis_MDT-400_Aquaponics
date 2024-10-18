#ifndef CRC16_H_
#define CRC16_H_
#include "globals.h"
#include <array>
// For fixed size command
std::array<uint8_t, 8> command_processor(std::array<uint8_t, 6> &data);
// For dynamic size command
uint8_t *special_command_processor(uint8_t *data, size_t size);
#endif