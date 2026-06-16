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

/*******************************************************************************
 * Network Configuration 
 ******************************************************************************/
#define WIFI_NAME SECRET_WIFI_NAME
#define WIFI_PASSWORD SECRET_WIFI_PASSWORD
#define MQTT_BROKER_IP SECRET_MQTT_BROKER_IP
#define MQTT_BROKER_PORT SECRET_MQTT_BROKER_PORT
#define MOSQUITTO_USERNAME SECRET_MOSQUITTO_USERNAME
#define MOSQUITTO_PASSWORD SECRET_MOSQUITTO_PASSWROD

/*******************************************************************************
 * Sensor Configuration 
 ******************************************************************************/
#define DS18B20_GPIO_PIN 4
#define LIQUID_SENSOR_GPIO_PIN 34
#define TDS_SENSOR_GPIO_PIN 35
#define CQRSENTDS01_GPIO_PIN 35

// TODO: In the future, we could hae more resolved
// read intervals (e.g. each sensor could be configured)
#define DEFAULT_READ_INTERVAL 3000

/*******************************************************************************
 * Device Configuration 
 ******************************************************************************/
#define PREFERENCE_NAMESPACE "tankwatch"