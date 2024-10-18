#ifndef MODBUSRST485_H
#define MODBUSRST485_H
#include <globals.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include "MQTT_Task.h"
#include "../configs/sensors/sensor_config.h"
#include "../hardwares/Sensor.h"
void modbus485_communicate_init();
#endif