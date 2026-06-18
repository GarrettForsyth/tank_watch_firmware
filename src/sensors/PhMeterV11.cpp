#include "PhMeterV11.h"
#include <Arduino.h>

PhMeterV11::PhMeterV11(uint8_t pin): SensorGPIO(pin) {
    _calibration = getOrDefaultPhCalibration();
}

void PhMeterV11::begin() {
  pinMode(_pin, INPUT);
}

void PhMeterV11::read() {
    int raw = analogRead(_pin);
    Serial.printf("raw ph = %d\n", raw);
    float voltage = raw * (ADC_VREF / ADC_MAX);
    Serial.printf("raw ph v = %f\n", voltage);
    _lastPh = _calibration.slope * voltage + _calibration.offset;
    Serial.printf("calb ph v = %f\n", _lastPh);
}

const SensorValue PhMeterV11::getReading() {
    return SensorValue::ofFloat(_lastPh);
}

const char* PhMeterV11::getModel() { return MODEL_NAME; }
const SensorType PhMeterV11::getType() { return SensorType::Ph; }
