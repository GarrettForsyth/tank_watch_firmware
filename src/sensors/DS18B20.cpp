#include "DS18B20.h"

DS18B20::DS18B20(uint8_t pin): oneWire(pin), sensors(&oneWire) {}

void DS18B20::begin() {
    sensors.begin();
}

void DS18B20::read() {
    sensors.requestTemperatures();
    lastReadTemperature = sensors.getTempCByIndex(0);
}

float DS18B20::getTemperature() {
    return lastReadTemperature;
}

const char* DS18B20::getModel() { return "DS18B20"; }

DS18B20::~DS18B20() {}