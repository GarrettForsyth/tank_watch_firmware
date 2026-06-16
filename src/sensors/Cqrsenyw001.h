/**
 * Filename: LiquidSensor.h
 * Author: Garrett Forsyth
 * Date: June 15 2026
 * Description: This file contains declarations for a simple liquid sensor.
 * Note: By convention, we expect a status of HIGH to mean water is detected,
 * though this could be changed using the phsyical switch on the sensor.
 */
#pragma once
#include "SensorGPIO.h"
#include <stdint.h>
#include "esp32-hal-gpio.h"

class Cqrsenyw001: public SensorGPIO {
public:

    /**
     * Construct a new liquid sensor object.
     * 
     * Parameters:
     * pin: The GPIO to use for this sensor.
     */
    Cqrsenyw001(uint8_t pin): SensorGPIO(pin) {};

    void begin() override;
    void read() override;
    const SensorValue getReading() override;
    const SensorType getType() override;
    const char* getModel() override;
    ~Cqrsenyw001() {};
private:
    const char* MODEL_NAME = "CQRSENYW001"; // From http://www.cqrobot.wiki/index.php/Non-Contact_Water/Liquid_Level_Sensor_SKU:_CQRSENYW001
    float lastReadStatus = LOW;
};