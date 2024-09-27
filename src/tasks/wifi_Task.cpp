#include "wifi_Task.h"

const char* ssid = PROJECT_WIFI_SSID;
const char* password = PROJECT_WIFI_PASSWORD;

void wifiTask(void *pvParameters) {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.print("ESP IP Address: http://");
  Serial.println(WiFi.localIP());
  vTaskDelete(NULL);  // Delete the task when done
}

void wifi_init(){
    xTaskCreate(wifiTask, "WiFiTask", 4096, NULL, 1, NULL);
}