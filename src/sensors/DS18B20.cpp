#include "DS18B20.h"

DS18B20::DS18B20(uint8_t pin): oneWire(pin), sensors(&oneWire) {}

void DS18B20::begin() {
    sensors.begin();
    readRomSensorAddress();
}

// Make sure sensors.begin() is called  prior to calling this
// For the DS18B20, the rom address is how it is uniquely identified
void DS18B20::readRomSensorAddress() {
    const char* addressFormat = "%02X%02X%02X%02X%02X%02X%02X%02X";
    const char* addressDefault = "0000000000000000";
    uint8_t romAddressBuffer[8];
    // Read the address and convert it to a string
    if (sensors.getAddress(romAddressBuffer, 0)) {
        snprintf(
            romSensorAddress,
            sizeof(romSensorAddress),
            addressFormat,
            romAddressBuffer[0],
            romAddressBuffer[1],
            romAddressBuffer[2],
            romAddressBuffer[3],
            romAddressBuffer[4],
            romAddressBuffer[5],
            romAddressBuffer[6],
            romAddressBuffer[7]
        );
    } else {
        strncpy(romSensorAddress, addressDefault, sizeof(romSensorAddress));
    }
}

void DS18B20::read() {
    sensors.requestTemperatures();
    lastReadTemperature = sensors.getTempCByIndex(0);
}

float DS18B20::getTemperature() {
    return lastReadTemperature;
}

const char* DS18B20::getModel() { return MODEL_NAME; }

const char* DS18B20::getId() { return romSensorAddress; }

DS18B20::~DS18B20() {}
