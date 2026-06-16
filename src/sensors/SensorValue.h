/**
 * Filename: SensorValue.h
 * Author: Garrett Forsyth
 * Date: June 16 2026
 * Description: Union of types sensor readings can take.
 */
#pragma once
#include <stdio.h>
#include <stddef.h>
struct SensorValue {
    static const int SENSOR_VALUE_SIZE = 16;
    enum class Type { Float, Bool } type;
    union { float f; bool b; };

    static SensorValue ofFloat(float v) { SensorValue s; s.type = Type::Float; s.f = v; return s; }
    static SensorValue ofBool(bool v)   { SensorValue s; s.type = Type::Bool;  s.b = v; return s; }

    void toString(char *buf, size_t len) const {
        switch (type) {
        case Type::Float: snprintf(buf, len, "%f", f); break;
        case Type::Bool: snprintf(buf, len, "%d", b); break;
        }
    }
};