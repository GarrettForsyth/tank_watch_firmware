#include "MQTTService.h"
#include "sensors/SensorValue.h"
#include "config.h"
#include <Arduino.h>

MQTTService::MQTTService(): mqttClient(wifiClient) {}

void MQTTService::begin() {
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(true);  // let the driver retry as well

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
    mqttClient.setSocketTimeout(SOCKET_TIMEOUT_S);

    WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
    lastOnlineMs = millis();
}

void MQTTService::loop() {
    const uint32_t now = millis();

    if (isOnline()) {
        lastOnlineMs = now;
        mqttClient.loop();
        return;
    }

    if (now - lastOnlineMs >= OFFLINE_RESTART_MS) {
        Serial.println("Offline for 10 minutes; restarting.");
        ESP.restart();
    }

    if (WiFi.status() != WL_CONNECTED) {
        if (now - lastWifiAttemptMs >= WIFI_RETRY_MS) {
            lastWifiAttemptMs = now;
            Serial.printf("Wi-Fi down (status %d); reconnecting...\n", WiFi.status());
            WiFi.disconnect();
            WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
        }
        return;
    }

    // If Wi-Fi is connected but MQTT is not, attempt to reconnect to the broker
    if (now - lastMqttAttemptMs >= MQTT_RETRY_MS) {
        lastMqttAttemptMs = now;
        Serial.print("Connecting to MQTT broker...");
        if (mqttClient.connect(deviceId, MOSQUITTO_USERNAME, MOSQUITTO_PASSWORD)) {
            Serial.println(" connected");
        } else {
            Serial.printf(" failed, rc=%d\n", mqttClient.state());
        }
    }
}

void MQTTService::publishReading(Sensor* sensor) {
    if (!isOnline()) return;

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

bool MQTTService::isOnline() {
    return WiFi.status() == WL_CONNECTED && mqttClient.connected();
}