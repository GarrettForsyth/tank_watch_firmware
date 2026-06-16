#include "SensorType.h"

const char* sensorTypeName(SensorType type) {
    switch (type) {
        case SensorType::Temperature: return "temperature";
        case SensorType::Liquid:      return "liquid";
        default:                      return "unknown";
    }
}