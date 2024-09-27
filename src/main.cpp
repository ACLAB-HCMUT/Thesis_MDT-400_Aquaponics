// Import required libraries
#include "globals.h"
void setup()
{
  Serial.begin(B115200);
  Serial1.begin(B9600, SERIAL_8N1, RXD_RELAY, TXD_RELAY);

  CreateTask();
}

void loop()
{
  // Nothing to do here, FreeRTOS tasks handle the work
  // uint8_t readValues[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xc4, 0x0b};
  uint8_t readValues[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A};
  uint8_t buffer[7];
  int n = Serial1.write(readValues, sizeof(readValues));
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
  delay(1000);
}