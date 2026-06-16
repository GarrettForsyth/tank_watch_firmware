#include "SensorBroker.h"

SensorBroker& SensorBroker::getInstance() {
    static SensorBroker instance;
    return instance;
}

void SensorBroker::publish(
    SensorType type,
    const char* sensorId,
    SensorValue value
) {
    _byType[type] = value;
    _byId[std::string(sensorId)] = value;
}

SensorValue SensorBroker::getLatest(SensorType type, SensorValue fallback) const {
    auto it = _byType.find(type);
    return (it != _byType.end()) ? it->second : fallback;
}

SensorValue SensorBroker::getLatest(const char* sensorId, SensorValue fallback) const {
    auto it = _byId.find(sensorId);
    return (it != _byId.end()) ? it->second : fallback;
}