#include "MQTTService.h"
#include "config.h"
#include <Arduino.h>

MQTTService::MQTTService(): mqttClient(wifiClient) {}

void MQTTService::begin() {
    connectWifi();

    // Get the MAC after connection to WIFI
    String mac = WiFi.macAddress();
    mac.replace(":", "");
    strlcpy(deviceId, mac.c_str(), sizeof(deviceId));

    // Set the topic string using the device id
    snprintf(
        temperatureTopic,
        sizeof(temperatureTopic),
        "tankwatch/%s/readings/temperature",
        deviceId
    );

    mqttClient.setServer(MQTT_BROKER_IP, MQTT_BROKER_PORT);
    connectMQTT();
}

void MQTTService::loop() {
    if (!mqttClient.connected()) {
        connectMQTT();
    }
    mqttClient.loop();
}

void MQTTService::publishTemperature(float celsius, const char* sensorModel) {
    if (!mqttClient.connected()) {
        connectMQTT();
    }

    // Add the sensor model to the temperature topic
    char topicWithModel[MAX_TOPIC_LENGTH];
    snprintf(
        topicWithModel,
        sizeof(topicWithModel),
        "%s/%s",
        temperatureTopic,
        sensorModel
    );

    char payload[PAYLOAD_LENGTH];
    snprintf(
        payload,
        sizeof(payload),
        "{\"value\":%f}",
        celsius
    );
    mqttClient.publish(topicWithModel, payload);
}

void MQTTService::connectWifi() {
    Serial.print("Connecting to WiFi");
    WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" connected");
}

void MQTTService::connectMQTT() {
    while (!mqttClient.connected()) {
        Serial.print("Connecting to MQTT broker...");
        if (mqttClient.connect(deviceId, MOSQUITTO_USERNAME, MOSQUITTO_PASSWORD)) {
            Serial.println(" connected");
        } else {
            Serial.print(" failed, rc=");
            Serial.println(mqttClient.state());
            delay(2000);
        }
    }
}