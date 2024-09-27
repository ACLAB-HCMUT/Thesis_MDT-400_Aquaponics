#ifndef GLOBALS_H
#define GLOBALS_H
#include <HardwareSerial.h>
#include "defines.h"
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "DHT20.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../project_config.h"
// TASK CONFIG
#include "../src/tasks/CreateTask.h"

#define TXD_RELAY 6
#define RXD_RELAY 7
#endif