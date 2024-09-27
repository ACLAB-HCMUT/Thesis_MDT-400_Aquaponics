#include "modus485_Task.h"
// int modbus_rs485_read(size_t returnSize)
// {
//     byte buffer[9];
//     size_t bytesRead = Serial1.readBytes(buffer, 9);
//     Serial.println("====SENSOR DATA====");
//     for (int i = 0; i < bytesRead; ++i)
//     {
//         Serial.print(static_cast<int>(buffer[i]), HEX);
//         Serial.print(" ");
//     }
//     Serial.println("");
//     Serial.println("============");
//     memset(buffer, 0, sizeof(buffer));
//     return (int)bytesRead;
// }
// void modbus_rs485_write(sReadCommand *command)
// {
//     int n = Serial1.write(command->buffer, sizeof(command->buffer));
//     // uint8_t readValue[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xc4, 0x0b};
//     // int n = Serial1.write(readValue, sizeof(readValue));
//     // if (n < 0)
//     // {
//     //     Serial.print("Cannot write");
//     // }
//     // else
//     // {
//     //     Serial.print("Write successfully: ");
//     // }
//     Serial1.flush();
// }

void modbus485_sensor_read(void *pvParameters)
{
    // sReadCommand *command = reinterpret_cast<sReadCommand *>(pvParameters);
    uint8_t readValue[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xc4, 0x0b};
    uint8_t buffer[7];
    while (true)
    {
        // modbus_rs485_write(command);
        // modbus_rs485_read(command->returnSize);
        int n = Serial1.write(readValue, sizeof(readValue));
        if (n > 0)
        {
            Serial.print("Sent: ");
            Serial.println(n);
        }
        Serial1.flush();

        size_t bytesRead = Serial1.readBytes(buffer, sizeof(buffer));
        // Serial.println("==== SENSOR DATA ====");
        Serial.print(bytesRead);

        for (int i = 0; i < bytesRead; ++i)
        {
            Serial.print(static_cast<int>(buffer[i]), HEX);
            Serial.print(" ");
        }
        Serial.println("");
        memset(buffer, 0, sizeof(buffer));
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}
void modbus485_sensor_read_init(uint8_t *buffer, size_t returnSize)
{
    sReadCommand command = {buffer, returnSize};
    xTaskCreate(modbus485_sensor_read, "MODBUS_485_READ", 4096, (void *)&command, 1, NULL);
}