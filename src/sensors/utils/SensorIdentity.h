/**
 * Filename: SensorIdentity.h
 * Author: Garrett Forsyth
 * Date: June 15 2026
 * Description:
 * To uniquely identify each sesnor, we'll generate a random ID and
 * store it in the device preferences using the model_gpio as a key.
 * 
 * Note: This key naming convention might need to be rethought if
 * sensors on I2C/SPI are introduced, but for now it works.
 */
#pragma once
#include <Preferences.h>
#include <stdint.h>

/**
 * Try to get the sensor id from shared preferences. If it does not
 * exist, create one.
 * Parameters:
 *   const char* model - name of the model of the sensor (used in preference key)
 *   uint8_t gpio - name of gpio pin sensor is attached to (used in preference key)
 * Returns: A 128-bit random id unique to this sesnor.
 */
const char* getOrCreateSensorId(const char* model, uint8_t gpio);

static const int MAX_KEY_LENGTH = 16;
static const int MAX_VALUE_LENGTH = 33;