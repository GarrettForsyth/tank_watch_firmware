#include "DS18B20.h"
#include "utils/SensorIdentity.h"

void DS18B20::begin() {
    sensors.begin();

    // Debug: report what is on the 1-Wire bus. 0 devices means a wiring or
    // pull-up problem (data needs ~4.7k to 3.3V).
    uint8_t count = sensors.getDeviceCount();
    Serial.printf("[DS18B20] GPIO %u: found %u device(s) on the 1-Wire bus\n", _pin, count);
    Serial.printf("[DS18B20] parasite power: %s\n", sensors.isParasitePowerMode() ? "yes" : "no");

    DeviceAddress address;
    if (count > 0 && sensors.getAddress(address, 0)) {
        Serial.print("[DS18B20] device 0 ROM: ");
        for (uint8_t i = 0; i < 8; i++) Serial.printf("%02X", address[i]);
        Serial.println();
    }
}

void DS18B20::read() {
    sensors.requestTemperatures();
    lastReadTemperature = sensors.getTempCByIndex(0);

    // DallasTemperature returns DEVICE_DISCONNECTED_C (-127) when no sensor
    // answers. hasValidReading() keeps that value from being published.
    if (!hasValidReading()) {
        Serial.printf("[DS18B20] GPIO %u: no response (read -127), %u device(s) on bus; not publishing\n",
                      _pin, sensors.getDeviceCount());
    }
}

bool DS18B20::hasValidReading() {
    return lastReadTemperature != DEVICE_DISCONNECTED_C;
}

const SensorValue DS18B20::getReading() {
    return SensorValue::ofFloat(lastReadTemperature);
}

const SensorType DS18B20::getType() {
    return SensorType::Temperature;
}

const char* DS18B20::getModel() { return MODEL_NAME; }

DS18B20::~DS18B20() {}
