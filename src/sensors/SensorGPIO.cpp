#include "SensorGPIO.h"
#include "./utils/SensorIdentity.h"

SensorGPIO::SensorGPIO(uint8_t pin): _pin(pin) {}

const char* SensorGPIO::getId() { 
    return getOrCreateSensorId(getModel(), _pin); 
}
