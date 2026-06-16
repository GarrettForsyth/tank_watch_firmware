/**
 * Filename: SensorBroker.h
 * Author: Garrett Forsyth
 * Date: June 16 2026
 * Description: Broker for sensors to share reading data.
 * 
 * This is important since some sensors depend on other reading
 * data (ex, tds and pH depend on temperature).
 */
#pragma once
#include <map>
#include "sensors/SensorType.h"
#include "sensors/SensorValue.h"

class SensorBroker {
public:
    // Singleton
    static SensorBroker& getInstance();

    void publish(SensorType type, const char* sensorId, SensorValue value);

    // Gets the latest value by sensor type
    SensorValue getLatest(SensorType type, SensorValue fallback) const;

    // Gets the sensor value from a particular sensor
    SensorValue getLatest(const char* sensorId, SensorValue fallback) const;

private:
    SensorBroker() = default;
    std::map<SensorType, SensorValue> _byType;
    std::map<std::string, SensorValue> _byId;
};