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
#include "SensorType.h"

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
    const char* getReading() override;
    const SensorType getType() override;
    const char* getModel() override;
    const char* getId() override;
    ~DS18B20() override;
private:
    const static uint8_t ROM_SENSOR_ADDRESS_SIZE = 17; // 16 hex char + terminator 
    const char* MODEL_NAME = "DS18B20";

    char romSensorAddress[ROM_SENSOR_ADDRESS_SIZE]; // 0's on read failure
    float lastReadTemperature = 0;
    OneWire oneWire;
    DallasTemperature sensors;

    void readRomSensorAddress(); // Call only after sensors.begin()
};