#include "Sensor.h"
#include <Arduino.h>

void Sensor::loop() {
    if (millis() - lastRead > interval) {
        read();
        lastRead = millis();
    }
}