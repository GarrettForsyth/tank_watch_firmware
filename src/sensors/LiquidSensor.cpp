#include "LiquidSensor.h"
#include "utils/SensorIdentity.h"

void LiquidSensor::begin() {
  pinMode(_pin, INPUT);
}

void LiquidSensor::read() {
    lastReadStatus = digitalRead(_pin);
}

int LiquidSensor::getStatus() {
    return lastReadStatus;
}

const char* LiquidSensor::getModel() { return MODEL_NAME; }

const char* LiquidSensor::getReading() {
    static char readingStr[READING_SIZE] = { 0 }; 
    snprintf(readingStr, sizeof(readingStr), "%d", getStatus());
    return readingStr;
}

const SensorType LiquidSensor::getType() {
    return SensorType::Liquid;
}

LiquidSensor::~LiquidSensor() {}
