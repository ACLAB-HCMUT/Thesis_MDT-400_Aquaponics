#include "modus485_Task.h"
const char *portname = PORT_USB;
int fd = -1;
const unsigned char readValue[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xc4, 0x0b};
int port_init()
{
    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0)
    {
        Serial.println("Error opening: ");
        Serial.println(portname);
    }
    return fd;
}
void port_close()
{
    close(fd);
}
void clearSerialBuffer()
{
    if (tcflush(fd, TCIFLUSH) != 0)
    {
        Serial.println("Error clearing serial buffer");
    }
}
bool port_config(speed_t speed)
{
    struct termios tty;
    if (tcgetattr(fd, &tty) != 0)
    {
        Serial.println("Error tcggetattr");
    }
    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit characters
    tty.c_iflag &= ~IGNBRK;                     // disable break processing
    tty.c_lflag = 0;                            // no signaling chars, no echo, no canonical processing
    tty.c_oflag = 0;                            // no remapping, no delays
    tty.c_cc[VMIN] = 0;                         // read doesn't block
    tty.c_cc[VTIME] = 5;                        // 0.5 seconds read timeout
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);     // shut off xon/xoff ctrl
    tty.c_cflag |= (CLOCAL | CREAD);            // ignore modem controls, enable reading
    tty.c_cflag &= ~(PARENB | PARODD);          // shut off parity

    if (tcsetattr(fd, TCSANOW, &tty) != 0)
    {
        Serial.println("Error from tcsetattr");
        return false;
    }
    return true;
}
int modbus_rs485_read(unsigned char *buffer, size_t size)
{
    size_t totalRead = 0;
    while (totalRead < size)
    {
        int bytesRead = read(fd, buffer, size - totalRead);
        if (bytesRead < 0)
        {
            Serial.println("FAILED READ");
            return -1;
        }
        totalRead += bytesRead;
    }
    int n = (int)totalRead;
    Serial.print("Number of bytes have been read: ");
    Serial.println(n);
    Serial.println("Read from serial port: ");
    for (int i = 0; i < n; ++i)
    {
        Serial.print(static_cast<int>(buffer[i]));
    }
    return (int)totalRead;
}
int modbus_rs485_write(const unsigned char *buffer, size_t size)
{
    return write(fd, buffer, size);
}
void modbus_rs485_init()
{
    fd = port_init();
    if (fd > 0)
    {
        if (!port_config(B9600))
            port_close();
    }
    clearSerialBuffer();
}