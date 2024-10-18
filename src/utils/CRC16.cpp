#include "globals.h"
#include "CRC16.h"
/**
 * @brief Each command have different command content, this function will generate CRC-16 checksum for
 * different command.
 *
 * Args: const array<uint8_t, 6> &data: command content
 */
std::array<uint8_t, 2> calculate_CRC(const std::array<uint8_t, 6> &data)
{
    uint16_t crc = 0xffff;
    for (size_t i = 0; i < data.size(); i++)
    {
        crc ^= data[i];
        for (int j = 0; j < 8; j++)
        {
            if (crc & 1) // check the LSB
            {
                crc >>= 1;
                // need to do this step because LSB = 1 -> means the remainder needs to be adjusted (CRC-16 rules)
                // Giống như là khi chia 1 số nhiều chữ số cho 1 số ít chữ số hơn, trong lúc chia mà có số dư -> cần phải điều chỉnh
                crc ^= 0xA001; // CRC-16 polynomial IBM
            }
            else
                crc >>= 1;
        }
    }
    std::array<uint8_t, 2> res;
    res[0] = static_cast<uint8_t>(crc & 0xFF);
    res[1] =
        static_cast<uint8_t>((crc >> 8) & 0xFF);
    return res;
}

/**
 * @brief Generate CRC-16 CheckSum bytes for command
 *
 * Arg: array<uint8_t, 6> &data: command content
 */
std::array<uint8_t, 8> command_processor(std::array<uint8_t, 6> &data)
{
    size_t size = data.size();
    std::array<uint8_t, 2> crc = calculate_CRC(data);
    std::array<uint8_t, 8> command;
    for (int i = 0; i < size; i++)
    {
        command[i] = data[i];
    }
    command[size] = crc[0];
    command[size + 1] = crc[1];
    return command;
}

uint8_t *special_command_processor(uint8_t *data, size_t size)
{
    Serial.print("Developiing");
    return {};
}