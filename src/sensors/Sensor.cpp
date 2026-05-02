#include "Sensor.h"
#include <Arduino.h>

bool Sensor::loop() {
    bool wasRead = false;
    if (millis() - lastRead > interval) {
        read();
        lastRead = millis();
        wasRead = true;
    }

    return wasRead;
}