#include "mqtt_Task.h"
WiFiClient wifiClient;
// DOCUMENT: https://pubsubclient.knolleary.net/api
PubSubClient client(wifiClient);

/**
 * @brief Setting call back when the client have subscribed to the topic
 * process the new message when it arrives.
 *
 */
void callback(char *topic, byte *payload, unsigned int length)
{
    String message;
    for (unsigned int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }
    Serial.println(message);
}

/**
 * @brief Publish data to a specific feed
 *
 */
void publishData(String feed, String data)
{
    // feed MQTT link
    String topic = String(IO_USERNAME) + "/feeds/" + feed;
    // check client connected
    if (client.connected())
    {
        client.publish(topic.c_str(), data.c_str());
    }
}
/**
 * @brief Main task of MQTT
 *
 */
void MQTTTask(void *pvParameters)
{
    // Check wifi connection
    while (WiFi.status() != WL_CONNECTED)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(callback);

    while (!client.connected())
    {
        Serial.println("Connecting to MQTT...");
        String clientID = "ESP32S3Client" + String(random(0, 1000));
        // connect to server
        if (client.connect(clientID.c_str(), IO_USERNAME, IO_KEY))
        {
            Serial.println("Connected to MQTT Server");
            client.subscribe("phongcute/feeds/test01");
            String sendData = WiFi.localIP().toString();
            publishData("ip", sendData);
            Serial.println(sendData);
            Serial.println("Started");
            while (true)
            {
                // maintain connection to server
                client.loop();
                vTaskDelay(100 / portTICK_PERIOD_MS);
            }
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            vTaskDelay(12000 / portTICK_PERIOD_MS);
        }
    }
}
/**
 * @brief Reconnect to MQTT sever when disconnected
 *
 */
void reconnect()
{
    xTaskCreate(MQTTTask, "MQTTTasks", 4096, NULL, 1, NULL);
}

void mqtt_init()
{
    xTaskCreate(MQTTTask, "MQTTTasks", 4096, NULL, 1, NULL);
}