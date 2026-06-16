#include "MQTTService.h"
#include "sensors/SensorValue.h"
#include "config.h"
#include <Arduino.h>

MQTTService::MQTTService(): mqttClient(wifiClient) {}

void MQTTService::begin() {
    connectWifi();

    // Get the MAC after connection to WIFI
    String mac = WiFi.macAddress();
    mac.replace(":", "");
    strlcpy(deviceId, mac.c_str(), sizeof(deviceId));

    // Set the base topic string using the device id
    snprintf(
        topicBase,
        sizeof(topicBase),
        "tankwatch/%s/readings",
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

void MQTTService::publishReading(Sensor* sensor) {
    if (!mqttClient.connected()) {
        connectMQTT();
    }

    // Determine the topic to publish to
    char fullTopic[MAX_TOPIC_LENGTH];
    snprintf(
        fullTopic,
        sizeof(fullTopic),
        "%s/%s/%s/%s",
        topicBase,
        sensorTypeName(sensor->getType()),
        sensor->getModel(),
        sensor->getId()
    );

    char readingBuf[SensorValue::SENSOR_VALUE_SIZE] = { 0 };
    sensor->getReading().toString(readingBuf, sizeof(readingBuf));
    char payload[PAYLOAD_LENGTH];
    snprintf(
        payload,
        sizeof(payload),
        "{\"value\":%s}",
        readingBuf
    );
    mqttClient.publish(fullTopic, payload);
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