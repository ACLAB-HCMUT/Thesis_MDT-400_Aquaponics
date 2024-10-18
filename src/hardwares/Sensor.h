#ifndef SENSOR_H_
#define SENSOR_H_
#include "../utils/CRC16.h"
#include "../utils/convert.h"
#include "../tasks/mqtt_Task.h"
#include <string>
#include <array>
#include <map>
#include "../configs/sensors/sensor_config.h"
typedef std::array<uint8_t, 6> RawCommand;

class Sensor
{
protected:
    std::map<std::string, std::array<uint8_t, 8>> commandMap;
    uint8_t slaveId;

public:
    Sensor() {}
    Sensor(uint8_t slaveId, const std::map<std::string, RawCommand> &cmdMap) : slaveId(slaveId)
    {
        for (auto command : cmdMap)
        {
            std::array<uint8_t, 8> commandWithCRC = command_processor(command.second);
            commandMap[command.first] = commandWithCRC;
        }
    };
    virtual void handleResponse(const uint8_t *response, size_t size, std::string commandName) = 0;
    virtual void addCommand(const std::string &cmdName, const RawCommand &cmd);
    virtual std::array<uint8_t, 8> getCommand(const std::string &cmdName);
    virtual void printCommandMap();
    virtual ~Sensor() {};
};
// ISHC
class Sensor_ISHC : public Sensor
{
public:
    Sensor_ISHC(uint8_t slaveId, const std::map<std::string, RawCommand> &cmdMap);
    void handleResponse(const uint8_t *response, size_t size, std::string commandName);
    ~Sensor_ISHC() {}
};
// ISEC
class Sensor_ISEC : public Sensor
{
public:
    Sensor_ISEC(uint8_t slaveId, const std::map<std::string, RawCommand> &cmdMap);
    void handleResponse(const uint8_t *response, size_t size, std::string commandName);
    ~Sensor_ISEC() {}
};
// ISDC
class Sensor_ISDC : public Sensor
{
public:
    Sensor_ISDC(uint8_t slaveId, const std::map<std::string, RawCommand> &cmdMap);
    void handleResponse(const uint8_t *response, size_t size, std::string commandName);
    ~Sensor_ISDC() {}
};
#endif