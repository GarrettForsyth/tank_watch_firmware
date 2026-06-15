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

DS18B20 tempSensor = DS18B20(DS18B20_GPIO_PIN);
LiquidSensor liquidSensor = LiquidSensor(LIQUID_SENSOR_GPIO_PIN);
MQTTService mqttService = MQTTService();

void setup(void) {
  Serial.begin(9600);
  tempSensor.begin();
  liquidSensor.begin();
  mqttService.begin();
}

void loop(void) {
  if (tempSensor.loop()) {
    float temp = tempSensor.getTemperature();
    const char* model = tempSensor.getModel();
    const char* id = tempSensor.getId();
    mqttService.publishTemperature(temp, model, id);
  };

  if (liquidSensor.loop()) {
    int status = liquidSensor.getStatus();
    const char* model = liquidSensor.getModel();
    const char* id = liquidSensor.getId();
    mqttService.publishLiquidStatus(status, model, id);
  }

  mqttService.loop();
}