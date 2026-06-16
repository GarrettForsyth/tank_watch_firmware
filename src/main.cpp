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
#include "sensors/LiquidSensor.h"
#include "services/MQTTService.h"
#include <Wifi.h>


Sensor* sensors[] = {
  new DS18B20(DS18B20_GPIO_PIN),
  new LiquidSensor(LIQUID_SENSOR_GPIO_PIN)
};
MQTTService mqttService = MQTTService();

void setup(void) {
  Serial.begin(9600);
  for (Sensor* sensor : sensors) {
    sensor->begin();
  }
  mqttService.begin();
}

void loop(void) {
  for (Sensor* sensor : sensors) {
    if (sensor->loop()) {
      mqttService.publishReading(sensor);
    }
  }
  mqttService.loop();
}