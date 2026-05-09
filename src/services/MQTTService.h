/**
 * Filename: MQTTService.h
 * Author: Garrett Forsyth
 * Date: May 2 2026
 * Description: This file contains declarations the MQTT Service.
 * 
 * This class is used to publish data to the mqtt server. It 
 * requires setup and for it's loop() method to be called
 * inside the main loop to maintain its connection.
 * 
 * Topic structure:
 *   Publish:   tankwatch/{deviceId}/readings/temperature/{sensorModel}
 *   Subscribe: tankwatch/{deviceId}/config  (deferred)
 */
#pragma once
#include <PubSubClient.h>
#include <Wifi.h>
#define BASE_TOPIC_LENGTH 64
#define MAX_TOPIC_LENGTH 128
#define PAYLOAD_LENGTH 64
#define MAC_LENGTH 13 // Sanitized after removing ':'

class MQTTService {
public:
    /**
     * Set up the MQTT Service. The configuration
     * used is stored in [config.h].
     */
    MQTTService();

    /**
     * Connects to wifi and the mqtt broker.
     * To be called once in main setup.
     */
    void begin();

    /**
     * Maintains connection with the broker.
     * To be called within the main loop.
     */
    void loop();

    /**
     * Publish temperature data to the MQTT broker.
     * 
     * Parameters:
     * celsius: The temperature value in celsius.
     * sensorModel: The model name for the sensor reading.
     * sensorId: The sensor id for the sensor reading.
     */
    void publishTemperature(
        float celsius,
        const char* sensorModel,
        const char* sensorId
    );

private:
    WiFiClient wifiClient;
    PubSubClient mqttClient;
    char deviceId[MAC_LENGTH];
    char temperatureTopic[BASE_TOPIC_LENGTH];
    void connectWifi();
    void connectMQTT();
};