/**
 * Filename: config.h
 * Author: Garrett Forsyth
 * Date: May 1 2026
 * Description: Configuration parameters to use.
 * 
 * Note: This will depend on how the board is wired.
 */
#pragma once
#include "secrets.h"

// For now, assume an esp32 board
#include "boards/esp32.h"
#define ADC_VREF ESP32_ADC_VREF
#define ADC_MAX ESP32_ADC_MAX
#define ADC_MIN ESP32_ADC_MIN
/*******************************************************************************
 * Sensor Configuration 
 ******************************************************************************/
#define DS18B20_GPIO_PIN 4
#define CQRSENYW001_GPIO_PIN 34
#define CQRSENTDS01_GPIO_PIN 35
#define PH_METER_V_1_1_GPIO_PIN 32
// END ESP32 specific configurations

/*******************************************************************************
 * Network Configuration 
 ******************************************************************************/
#define WIFI_NAME SECRET_WIFI_NAME
#define WIFI_PASSWORD SECRET_WIFI_PASSWORD
#define MQTT_BROKER_IP SECRET_MQTT_BROKER_IP
#define MQTT_BROKER_PORT SECRET_MQTT_BROKER_PORT
#define MOSQUITTO_USERNAME SECRET_MOSQUITTO_USERNAME
#define MOSQUITTO_PASSWORD SECRET_MOSQUITTO_PASSWROD

// TODO: In the future, we could hae more resolved
// read intervals (e.g. each sensor could be configured)
#define DEFAULT_READ_INTERVAL 3000
