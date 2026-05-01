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

#define ONE_WIRE_BUS 4

class DS18B20: public Sensor {
public:
    /**
     * pin: The GPIO to use for this sensor.
     */
    DS18B20(uint8_t pin);
    void begin() override;
    void read() override;
    ~DS18B20() override;
private:
    OneWire oneWire;
    DallasTemperature sensors;
};