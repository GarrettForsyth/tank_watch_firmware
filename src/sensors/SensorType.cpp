#include "SensorType.h"

const char* sensorTypeName(SensorType type) {
    switch (type) {
        case SensorType::Temperature: return "temperature";
        case SensorType::Liquid:      return "liquid";
        case SensorType::Tds:         return "tds";
        default:                      return "unknown";
    }
}