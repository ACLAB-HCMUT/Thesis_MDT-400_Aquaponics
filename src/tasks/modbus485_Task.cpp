#include "modus485_Task.h"
HardwareSerial RS485Serial(1);
uint8_t sensorRead[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xc4, 0x0b};
std::string floatToString(float value) {
    // Extract integer part
    int intPart = static_cast<int>(value);
    // Extract fractional part
    float fracPart = value - intPart;

    // Convert integer part to string
    std::string result = "";
    if (intPart == 0) {
        result = "0";
    } else {
        while (intPart > 0) {
            result = static_cast<char>('0' + intPart % 10) + result;
            intPart /= 10;
        }
    }

    // Add decimal point
    result += ".";

    // Convert fractional part to string
    for (int i = 0; i < 6; ++i) { // Limiting to 6 decimal places
        fracPart *= 10;
        int digit = static_cast<int>(fracPart);
        result += static_cast<char>('0' + digit);
        fracPart -= digit;
    }

    return result;
}
void cleanBuffer()
{
    size_t bytesToRead = RS485Serial.available();
    if (bytesToRead > 0)
    {
        byte out[bytesToRead];
        RS485Serial.readBytes(out, bytesToRead);
    }
}
void read_from_sensor(int bufferSize)
{
    byte buffer[bufferSize];

    int avail = RS485Serial.available();
    if (avail > 0)
    {
        size_t bytesRead = RS485Serial.readBytes(buffer, sizeof(buffer));
        // for (int i = 0; i < bytesRead; i++)
        // {
        //     Serial.print(buffer[i], HEX);
        //     Serial.print(" ");
        // }
        Serial.println("");
        if (buffer[1] == 0x03)
        {
            float temperature = (buffer[3] << 8) | buffer[4]; // shift left 8 bits -> 2 bytes : 0xbuffer[3]00 ->  0xbuffer[3]buffer[4]
            temperature = temperature / 10;
            // Serial.print("Temperature: ");
            // Serial.println(temperature);
            float humidity = (buffer[5] << 8) | buffer[6]; // shift left 8 bits -> 2 bytes : 0xbuffer[3]00 ->  0xbuffer[3]buffer[4]
            humidity = humidity / 10;
            // Serial.print("Humidity: ");
            // Serial.println(humidity);
            publishData("TEMP", String(temperature));
            publishData("HUMI", String(humidity));
        }
        // Serial.println(bytesRead);
    }
    else
    {
        Serial.println("Lỗi đọc cảm biến");
    }
    memset(buffer, 0, sizeof(buffer));
}
void write_to_sensor()
{
    cleanBuffer();
    int n = RS485Serial.write(sensorRead, sizeof(sensorRead));
}
void modbus485_sensor_read(void *pvParameters)
{
    while (true)
    {
        write_to_sensor();
        vTaskDelay(100/portTICK_PERIOD_MS);
        read_from_sensor(BUFFER_SIZE);
        vTaskDelay(7000/portTICK_PERIOD_MS);
    }
}
void modbus485_sensor_read_init()
{
    RS485Serial.begin(9600, SERIAL_8N1, RXD_RELAY, TXD_RELAY);
    xTaskCreate(modbus485_sensor_read, "MODBUS_485_READ", 4096, NULL, 1, NULL);
}