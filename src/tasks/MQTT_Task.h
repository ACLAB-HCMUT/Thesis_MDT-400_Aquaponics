#ifndef MQTTTASK_H
#define MQTTTASK_H
#include "globals.h"
#include "defines.h"
#include <PubSubClient.h>
#include <Adafruit_MQTT.h>
extern PubSubClient client;
extern WiFiClient espClient;
void mqtt_init();
void publishData(String feed, String data);
#endif