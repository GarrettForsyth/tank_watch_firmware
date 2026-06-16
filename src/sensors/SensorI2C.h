/**
 * Filename: SensorI2C.h
 * Author: Garrett Forsyth
 * Date: May 1 2026
 * Description: A specialization for sensors using I2C.
 */
#pragma once
#include "Sensor.h"
#include "stdint.h"

class SensorI2C : public Sensor {
protected:
    const uint8_t _address;
public:
    SensorI2C(uint8_t address) : _address(address) {}
};