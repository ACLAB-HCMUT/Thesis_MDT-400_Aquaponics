#include "CreateTask.h"
uint8_t readValue[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xc4, 0x0b};
void CreateTask()
{
    // wifi_init();
    // server_init();
    modbus485_sensor_read_init(readValue, 9);
    // mqtt_init();
}