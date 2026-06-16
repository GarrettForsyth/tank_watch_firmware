/**
 * Filename: SensorType.h
 * Author: Garrett Forsyth
 * Date: June 15 2026
 * Description: Enumeration which defines types of supported sensors.
 */
#pragma once
enum class SensorType {
    Temperature,
    Liquid
};

/**
 * Get a string representation of the sensor type.
 */
const char* sensorTypeName(SensorType type);