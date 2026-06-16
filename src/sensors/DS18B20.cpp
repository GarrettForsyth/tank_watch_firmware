#include "DS18B20.h"
#include "utils/SensorIdentity.h"


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

const char* DS18B20::getReading() {
    static char readingStr[READING_SIZE] = { 0 }; 
    snprintf(readingStr, sizeof(readingStr), "%f", getTemperature());
    return readingStr;
}

const SensorType DS18B20::getType() {
    return SensorType::Temperature;
}

const char* DS18B20::getModel() { return MODEL_NAME; }

DS18B20::~DS18B20() {}
