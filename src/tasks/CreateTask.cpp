#include "CreateTask.h"
void CreateTask()
{
    wifi_init();
    server_init(); 
    modbus485_sensor_read_init();
    mqtt_init();
}