/**
 * Filename: Cqrsentds01.h
 * Author: Garrett Forsyth
 * Date: June 15 2026
 * Description: This file contains declarations for the cqrsentds01 TDS sensor.
 * 
 * See http://www.cqrobot.wiki/index.php/TDS_(Total_Dissolved_Solids)_Meter_Sensor_SKU:_CQRSENTDS01
 * 
 * Note: This sensor has two distinct intervals:
 *   1) sample - how long it should take to collect a sample
 *   2) publish - how often it should publish the median of the sample
 */
#pragma once
#include "SensorGPIO.h"

#define TDS_SAMPLE_COUNT 30
#define TDS_SAMPLE_INTERVAL_MS 40
#define TDS_DEFAULT_TEMP_CALB 25.0f
#define VREF 3.3f
#define ADC_RESOLUTION 4095.0f

class Cqrsentds01 : public SensorGPIO {
public:
    Cqrsentds01(uint8_t pin, unsigned long publishIntervalMs = 3000);

    void begin() override;
    void read() override;
    bool loop() override;
    const SensorValue getReading() override;
    const SensorType getType() override;
    const char* getModel() override;
    ~Cqrsentds01() {};

private:
    const char* MODEL_NAME = "CQRSENTDS01";

    unsigned long _publishIntervalMs;
    unsigned long _lastSampleTime;
    unsigned long _lastPublishTime;

    int _sampleBuffer[TDS_SAMPLE_COUNT];
    int _sampleIndex;

    static const int READING_BUF_SIZE = 16;
    char _readingBuf[READING_BUF_SIZE];
    float _lastTds;

    int getMedian();
};