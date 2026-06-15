/**
 * Filename: LiquidSensor.h
 * Author: Garrett Forsyth
 * Date: June 15 2026
 * Description: This file contains declarations for a simple liquid sensor.
 * Note: By convention, we expect a status of HIGH to mean water is detected,
 * though this could be changed using the phsyical switch on the sensor.
 */
#pragma once
#include "Sensor.h"
#include <stdint.h>
#include "esp32-hal-gpio.h"

class LiquidSensor: public Sensor {
public:

    /**
     * Construct a new liquid sensor object.
     * 
     * Parameters:
     * pin: The GPIO to use for this sensor.
     */
    LiquidSensor(uint8_t pin);

    /**
     * Gets the status of the sensor.
     * Returns: HIGH (0x1) when water is detected
     * and LOW (0x0) if not.
     */
    int getStatus();

    void begin() override;
    void read() override;
    const char* getModel() override;
    const char* getId() override;
    ~LiquidSensor() override;
private:
    const uint8_t GPIO_PIN;
    const char* MODEL_NAME = "CQRSENYW001"; // From http://www.cqrobot.wiki/index.php/Non-Contact_Water/Liquid_Level_Sensor_SKU:_CQRSENYW001
    float lastReadStatus = LOW;
};