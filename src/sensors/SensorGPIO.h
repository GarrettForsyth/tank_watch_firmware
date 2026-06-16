/**
 * Filename: SensorGPIO.h
 * Author: Garrett Forsyth
 * Date: May 1 2026
 * Description: A specialization for sensors using a GPIO pin.
 */
#pragma once
#include "Sensor.h"
#include "stdint.h"

class SensorGPIO: public Sensor {
public:
    SensorGPIO(uint8_t pin);
    const char* getId() override;
protected:
    const uint8_t _pin;
};