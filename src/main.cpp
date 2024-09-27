// Import required libraries
#include "globals.h"
void setup()
{
  Serial.begin(9600);
  CreateTask();
}
void loop()
{
  // Nothing to do here, FreeRTOS tasks handle the work
}