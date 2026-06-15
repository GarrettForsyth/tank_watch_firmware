#include "LiquidSensor.h"
#include "utils/SensorIdentity.h"

LiquidSensor::LiquidSensor(uint8_t pin): GPIO_PIN(pin) {}

void LiquidSensor::begin() {
  pinMode(GPIO_PIN, INPUT);
}

void LiquidSensor::read() {
    lastReadStatus = digitalRead(GPIO_PIN);
}

int LiquidSensor::getStatus() {
    return lastReadStatus;
}

const char* LiquidSensor::getModel() { return MODEL_NAME; }

const char* LiquidSensor::getId() { 
    return getOrCreateSensorId(MODEL_NAME, GPIO_PIN); 
}

LiquidSensor::~LiquidSensor() {}
