#ifndef MODBUSRST485_H
#define MODBUSRST485_H
#include <globals.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include "MQTT_Task.h"

// typedef struct READ_COMMAND_struct{
//     uint8_t * buffer;
//     size_t returnSize;
// } sReadCommand;

extern uint8_t sensorRead[];
void modbus485_sensor_read_init();
#endif