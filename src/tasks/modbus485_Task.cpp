#include "modus485_Task.h"
HardwareSerial RS485Serial(1);

Sensor_ISHC sensorISHC(ISHC_ID, {{MEASURE_PH, {ISHC_ID, 0x03, 0x00, 0x01, 0x00, 0x02}},
                                 {MEASURE_TEMP, {ISHC_ID, 0x03, 0x00, 0x03, 0x00, 0x02}}});

Sensor_ISEC sensorISEC(ISEC_ID, {{MEASURE_CONDUCT, {ISEC_ID, 0x03, 0x00, 0x00, 0x00, 0x02}},
                                 {MEASURE_RESIS, {ISEC_ID, 0x03, 0x00, 0x02, 0x00, 0x02}},
                                 {MEASURE_SALI, {ISEC_ID, 0x03, 0x00, 0x08, 0x00, 0x02}},
                                 {MEASURE_TDS, {ISEC_ID, 0x03, 0x00, 0x06, 0x00, 0x02}},
                                 {MEASURE_TEMP, {ISEC_ID, 0x03, 0x00, 0x04, 0x00, 0x02}}});

Sensor_ISDC sensorISDC(ISDC_ID, {{MEASURE_DO, {ISDC_ID, 0x03, 0x00, 0x01, 0x00, 0x02}},
                                 {MEASURE_TEMP, {ISDC_ID, 0x03, 0x00, 0x03, 0x00, 0x02}}});

/**
 * @brief Clean buffer to avoid error reading in port.
 *
 */
void clean_buffer()
{
    size_t bytesToRead = RS485Serial.available();
    if (bytesToRead > 0)
    {
        byte out[bytesToRead];
        RS485Serial.readBytes(out, bytesToRead);
    }
}
/**
 * @brief Receive data when having sent the command to the sensor.
 *
 * Args: int bufferSize: the size of buffer want to be read.
 *
 */
void read_from_sensor(Sensor &sensor, size_t bufferSize, std::string commandName)
{
    uint8_t buffer[bufferSize];

    int avail = RS485Serial.available();
    if (avail > 0)
    {
        size_t bytesRead = RS485Serial.readBytes(buffer, sizeof(buffer));
        sensor.handleResponse(buffer, sizeof(buffer), commandName);
    }
    else
    {
        Serial.println("Lỗi đọc cảm biến");
    }
    memset(buffer, 0, sizeof(buffer));
}
/**
 * @brief Send command to sensor
 *
 */
void write_to_sensor(Sensor &sensor, std::string commandName)
{
    std::array<uint8_t, 8> command = sensor.getCommand(commandName);
    uint8_t cmd[8];
    for (int i = 0; i < 8; ++i)
    {
        cmd[i] = command[i];
    }
    RS485Serial.write(cmd, sizeof(cmd));
}

/**
 * @brief Send command and read the returned from a specific sensor
 *
 * Sensor &sensor: sensor type
 *
 * std::string commandName: command name
 *
 * size_t bufferSize: returned buffer size
 *
 */
void read_value(Sensor &sensor, std::string commandName, size_t bufferSize)
{
    clean_buffer();
    write_to_sensor(sensor, commandName);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    read_from_sensor(sensor, bufferSize, commandName);
    vTaskDelay(100 / portTICK_PERIOD_MS);
}

/**
 * @brief Total flow of sending command to sensor and read the value sent back.
 *
 */
void modbus485_communication_loop(void *pvParameters)
{

    while (true)
    {
#ifdef ISDC_205
        read_value(sensorISDC, MEASURE_DO, 9);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        read_value(sensorISDC, MEASURE_TEMP, 9);
#endif
#ifdef ISEC_205
        read_value(sensorISEC, MEASURE_CONDUCT, 9);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        read_value(sensorISEC, MEASURE_TEMP, 9);
#endif
#ifdef ISHC_205
        read_value(sensorISHC, MEASURE_PH, 9);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        read_value(sensorISHC, MEASURE_TEMP, 9);
#endif
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
/**
 * @brief Init task for communicating with sensors by modbus RS485.
 *
 */
void modbus485_communicate_init()
{
    RS485Serial.begin(9600, SERIAL_8N1, RXD_RELAY, TXD_RELAY);
    xTaskCreate(modbus485_communication_loop, "MODBUS_485_READ", 4096, NULL, 1, NULL);
}