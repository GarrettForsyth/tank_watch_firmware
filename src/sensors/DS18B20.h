/**
 * Filename: DS18B20.h
 * Author: Garrett Forsyth
 * Date: May 1 2026
 * Description: This file contains declarations for the DS18B20 temperature sensor.
 */
#pragma once
#include "SensorGPIO.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "SensorType.h"
#include "SensorValue.h"

class DS18B20: public SensorGPIO {
public:
    /**
     * Construct a new DS18B20 sensor object.
     * 
     * Parameters:
     * pin: The GPIO to use for this sensor.
     */
    DS18B20(uint8_t pin): SensorGPIO(pin), oneWire(pin), sensors(&oneWire) {}

    void begin() override;
    void read() override;
    const SensorValue getReading() override;
    const SensorType getType() override;
    const char* getModel() override;
    ~DS18B20() override;
private:
    const char* MODEL_NAME = "DS18B20";
    float lastReadTemperature = 0;
    OneWire oneWire;
    DallasTemperature sensors;
};