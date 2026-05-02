/**
 * Filename: DS18B20.h
 * Author: Garrett Forsyth
 * Date: May 1 2026
 * Description: This file contains declarations for the DS18B20 temperature sensor.
 */
#pragma once
#include "Sensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class DS18B20: public Sensor {
public:
    /**
     * Construct a new DS18B20 sensor object.
     * 
     * Parameters:
     * pin: The GPIO to use for this sensor.
     */
    DS18B20(uint8_t pin);

    /**
     * Gets the last read temperature.
     */
    float getTemperature();

    void begin() override;
    void read() override;
    const char* getModel() override;
    ~DS18B20() override;
private:
    OneWire oneWire;
    DallasTemperature sensors;
    float lastReadTemperature = 0;
};