#include "LiquidSensor.h"
#include "utils/SensorIdentity.h"

void LiquidSensor::begin() {
  pinMode(_pin, INPUT);
}

void LiquidSensor::read() {
    lastReadStatus = digitalRead(_pin);
}

const char* LiquidSensor::getModel() { return MODEL_NAME; }

const SensorValue LiquidSensor::getReading() {
    return SensorValue::ofBool(lastReadStatus);
}

const SensorType LiquidSensor::getType() {
    return SensorType::Liquid;
}

LiquidSensor::~LiquidSensor() {}
