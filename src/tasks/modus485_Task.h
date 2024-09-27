#ifndef MODBUSRST485_H
#define MODBUSRST485_H
#include <globals.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
typedef struct READ_COMMAND_struct{
    uint8_t * buffer;
    size_t returnSize;
} sReadCommand;
void modbus485_sensor_read_init(uint8_t *buffer, size_t returnSize);
#endif