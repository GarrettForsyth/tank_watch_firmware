/**
 * Filename: SensorGPIO.h
 * Author: Garrett Forsyth
 * Date: June 18 2026
 * Description: This file contains declarations for pH meter v1.1 sensor.
 * 
 * See https://docs.cirkitdesigner.com/component/968ae382-87b6-4cd4-a87d-7529e2a0c468/ph-meter-v11
 * 
 * Note: This sensor requires calibration to give accurate readings. It can also
 * use either the 5V or 3.3V power. Currently 3.3V is used to be consistent
 * with other sensors, but if range becomes a problem we should consider moving it
 * to 5V.
 */
#pragma once
#include "SensorGPIO.h"
#include "calibration/PhCalibration.h"

class PhMeterV11 : public SensorGPIO {
public:
    PhMeterV11(uint8_t pin);

    void begin() override;
    void read() override;
    const SensorValue getReading() override;
    const SensorType getType() override;
    const char* getModel() override;
    ~PhMeterV11() {};

private:
    const char* MODEL_NAME = "PHMETERV11";
    PhCalibration _calibration;
    float _lastPh;
};