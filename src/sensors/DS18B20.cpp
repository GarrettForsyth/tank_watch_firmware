#include "DS18B20.h"

DS18B20::DS18B20(uint8_t pin): oneWire(pin), sensors(&oneWire) {}

void DS18B20::begin() {
    sensors.begin();
}

void DS18B20::read() {
    // TODO: For now, just print the readings to the console,
    // but in the future we shold publish them to MQTT or
    // return the value so a more specialized object can publish

    Serial.print("Requesting temperatures...");
    sensors.requestTemperatures(); // Send the command to get temperatures
    Serial.println("DONE");

    Serial.print("Temperature: ");
    Serial.println(sensors.getTempCByIndex(0));
}

DS18B20::~DS18B20() {}