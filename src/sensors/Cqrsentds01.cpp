#include "Cqrsentds01.h"
#include "services/SensorBroker.h"
#include "SensorType.h"
#include <Arduino.h>
#include <string.h>
#include <algorithm>

constexpr const int TDS_SAMPLE_INTERVAL_MS = 40;
constexpr const int TDS_DEFAULT_TEMP_CALB = 30;

Cqrsentds01::Cqrsentds01(uint8_t pin):  SensorGPIO(pin),
    _lastSampleTime(0),
    _lastPublishTime(0),
    _sampleIndex(0),
    _lastTds(0.0f) {
    memset(_sampleBuffer, 0, sizeof(_sampleBuffer));
    memset(_readingBuf, 0, sizeof(_readingBuf));
}

void Cqrsentds01::begin() {
  pinMode(_pin, INPUT);
}


void Cqrsentds01::read() {
    // Read the analog voltage from a more stable value by filtering the median
    // NOTE: ESP32 has 12 bit Analog-Digital-Converter (this differs compared to the datasheet example)
    float voltage = getMedian() * ADC_MAX / ADC_MAX;
    float temp = SensorBroker::getInstance().getLatest(
        SensorType::Temperature,
        SensorValue::ofFloat(TDS_DEFAULT_TEMP_CALB)
    ).f;
    float compensation = 1.0f + 0.02f * (temp - 25.0f); // Again, from the datasheet
    float compensatedV = voltage / compensation;

    // Calculation to convert voltage to tds. Taken from:
    // http://www.cqrobot.wiki/index.php/TDS_(Total_Dissolved_Solids)_Meter_Sensor_SKU:_CQRSENTDS01
    _lastTds = (
        133.42f *
        compensatedV *compensatedV * compensatedV -
            255.86f * compensatedV * compensatedV + 
            857.39f * compensatedV
    ) * 0.5f;
}

bool Cqrsentds01::loop() {
    unsigned long now = millis();

    // Take a sample reading if it's time
    if (now - _lastSampleTime >= TDS_SAMPLE_INTERVAL_MS) {
        _lastSampleTime = now;
        _sampleBuffer[_sampleIndex++] = analogRead(_pin);
        _sampleIndex = _sampleIndex % TDS_SAMPLE_COUNT;
    }

    // Update the latest reading if it's time
    if (now - _lastPublishTime >= interval) {
        _lastPublishTime = now;
        read();
        return true;
    }
    return false;
}

int Cqrsentds01::getMedian() {
    int temp[TDS_SAMPLE_COUNT];
    memcpy(temp, _sampleBuffer, sizeof(_sampleBuffer));
    std::sort(temp, temp + TDS_SAMPLE_COUNT);
    return (TDS_SAMPLE_COUNT & 1) ?
        temp[(TDS_SAMPLE_COUNT - 1) / 2 ] : // Odd - take the middle
        (temp[TDS_SAMPLE_COUNT / 2] + temp[(TDS_SAMPLE_COUNT - 1) / 2]) / 2; // Even average the middle 2 entries
}

const SensorValue Cqrsentds01::getReading() {
    return SensorValue::ofFloat(_lastTds);
}

const char* Cqrsentds01::getModel() { return MODEL_NAME; }

const SensorType Cqrsentds01::getType() { return SensorType::Tds; }

