/**
 * Filename: main.cpp
 * Author: Garrett Forsyth
 * Date: May 1 2026
 * Description: 
 * This program initializes all sensors, then defers to their loop
 * implementation. When new data is read, it is published to the
 * MQTT server.
 */
#include "config.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "sensors/DS18B20.h"

DS18B20 tempSensor = DS18B20(DS18B20_GPIO_PIN);

void setup(void) {
  Serial.begin(9600);
  tempSensor.begin();
}

void loop(void) {
  tempSensor.loop();
}