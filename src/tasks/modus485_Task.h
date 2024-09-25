#ifndef MODBUSRST485_H
#define MODBUSRST485_H
#include <globals.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
extern const char *portname;
void modbus_rs485_init();
int modbus_rs485_read(unsigned char *buffer, size_t size);
int modbus_rs485_write(const unsigned char *buffer, size_t size);
#endif