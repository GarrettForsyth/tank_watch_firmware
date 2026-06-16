#include "Cqrsenyw001.h"
#include "utils/SensorIdentity.h"

void Cqrsenyw001::begin() {
  pinMode(_pin, INPUT);
}

void Cqrsenyw001::read() {
    lastReadStatus = digitalRead(_pin);
}

const char* Cqrsenyw001::getModel() { return MODEL_NAME; }

const SensorValue Cqrsenyw001::getReading() {
    return SensorValue::ofBool(lastReadStatus);
}

const SensorType Cqrsenyw001::getType() {
    return SensorType::Liquid;
}