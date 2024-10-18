#include "Sensor.h"
void Sensor::addCommand(const std::string &cmdName, const RawCommand &cmd)
{
    std::array<uint8_t, 6> data;
    for (int i = 0; i < 6; i++)
    {
        data[i] = cmd[i];
    }
    std::array<uint8_t, 8> commandWithCRC = command_processor(data);
    commandMap[cmdName] = commandWithCRC;
}
std::array<uint8_t, 8> Sensor::getCommand(const std::string &cmdName)
{
    auto it = commandMap.find(cmdName);
    if (it != commandMap.end())
    {
        auto value = it->second;

        return value;
    }
    else
    {
        return {};
    }
}
void Sensor::printCommandMap()
{
    // std::cout << "Size: " << commandMap.size() << endl;
    Serial.print("Command Maps");
}

Sensor_ISHC::Sensor_ISHC(uint8_t slaveId, const std::map<std::string, RawCommand> &cmdMap) : Sensor(slaveId, cmdMap) {}
void Sensor_ISHC::handleResponse(const uint8_t *response, size_t size,std::string commandName)
{
    uint8_t value[4] = { response[5], response[6], response[3], response[4]};
    float res = convertToFloat(value);
    Serial.print(commandName.c_str());
    Serial.print("-ISHC: ");
    Serial.println(res);
}

Sensor_ISEC::Sensor_ISEC(uint8_t slaveId, const std::map<std::string, RawCommand> &cmdMap) : Sensor(slaveId, cmdMap) {};
void Sensor_ISEC::handleResponse(const uint8_t *response, size_t size,std::string commandName)
{
    uint8_t value[4] = { response[5], response[6], response[3], response[4]};
    float res = convertToFloat(value);
    Serial.print(commandName.c_str());
    Serial.print("-ISEC: ");
    Serial.println(res);
    // publishData("TEMP", String(res));
}

Sensor_ISDC::Sensor_ISDC(uint8_t slaveId, const std::map<std::string, RawCommand> &cmdMap) : Sensor(slaveId, cmdMap) {}
void Sensor_ISDC::handleResponse(const uint8_t *response, size_t size,std::string commandName)
{
    uint8_t value[4] = { response[5], response[6], response[3], response[4]};
    float res = convertToFloat(value);
    Serial.print(commandName.c_str());
    Serial.print("-ISDC: ");
    Serial.println(res);
}
