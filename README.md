# TankWatch — Firmware

TankWatch is a personal IoT aquarium monitoring system. I'm building it to collect data to help me understand what's 'really' happening inside my aquarium. I hope for it to one day give me insight
into why my fish and plants thrive.. or not. Plus it's a fun intersection between my interest in coding and fishkeeping.

Right now, the key features are:
- Visualizing historical sensor data through a mobile client app 
- Receiving alert notifications when sensor readings breach a configured threshold

The idea is sensors connected to an ESP32 board publish to an MQTT broker hosted in the cloud. The backend monitors incoming readings and alerts the mobile client when they breach their configured threshold. The backend also offers an API for the mobile client to gather historical sensor data.

This repo contains the ESP32 firmware: C++ (Arduino framework), PlatformIO, DS18B20 temperature sensing, and MQTT publishing.

**Related repos:** [tank_watch_server](https://github.com/garrettforsyth/tank_watch_server) · [tankwatch-android](https://github.com/garrettforsyth/tankwatch-android)

---

## Demo

![TankWatch Demo](docs/tankwatch_demo.gif)

---

## Overview
Currently the firmware only supports temperature readings from a DS18B20 sensor. It periodically publishes these readings to an MQTT broker (in the future, the publishing interval will be configurable, but for now it's hardcoded).

Roadmap:
- Additional sensor support: water level, total dissolved solids (TDS), pH
- Device provisioning flow
- Sensor configuration updates

## Hardware

| Component | Detail |
|---|---|
| Microcontroller | ESP32-WROOM-32 devkit (38-pin) |
| Temperature sensor | DS18B20 waterproof probe (1-Wire) |
| Pull-up resistor | 4.7kΩ between VCC and Data (required) |

### Wiring

| DS18B20 | ESP32 |
|---|---|
| VCC | 3.3V |
| Data | GPIO 4 (D4) |
| GND | GND |

> If `getTempCByIndex(0)` returns `-127.00`, this indicates a wiring or pin configuration error — check the pull-up resistor and the GPIO pin assignment in `config.h`.

---

## Getting Started

### Prerequisites

- [PlatformIO](https://platformio.org/) (VS Code extension recommended)
- [Silicon Labs CP210x Universal Windows Driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) (v11.5.0) — required for the CP2102 USB-to-serial chip on the ESP32 devkit

### 1. Clone the repo

```bash
git clone https://github.com/garrettforsyth/tankwatch-firmware
```

### 2. Create secrets.h

`secrets.h` is gitignored. Create it at `src/secrets.h`:

```cpp
#define SECRET_WIFI_SSID      "your_wifi_ssid"
#define SECRET_WIFI_PASSWORD  "your_wifi_password"
#define SECRET_MQTT_BROKER_IP "tankwatch.duckdns.org"
#define MQTT_USERNAME         "your_mqtt_username"
#define MQTT_PASSWORD         "your_mqtt_password"
```

For local development, set `SECRET_MQTT_BROKER_IP` to your machine's local IP address.

### 3. Flash

Connect the ESP32 via USB, then use PlatformIO's **Upload** button or:

```bash
pio run --target upload
```

Open the Serial Monitor at 9600 baud to verify WiFi and MQTT connection.

---

## MQTT

The firmware publishes a temperature reading every 30 seconds.

**Topic:**
```
tankwatch/{deviceId}/readings/temperature/ds18b20/{romAddress}
```

- `deviceId` — ESP32 MAC address, colons stripped (e.g. `A4CF12345678`), determined at runtime after WiFi connects
- `romAddress` — DS18B20 64-bit ROM address as hex string (e.g. `28FF70B85B64C87B`), read once at startup

**Payload:**
```json
{ "value": 24.0625 }
```

---

## Project Structure

```
tankwatch-firmware/
├── src/
│   ├── main.cpp
│   ├── config.h            ← pin assignments, broker address, includes secrets.h
│   ├── secrets.h           ← gitignored — WiFi + MQTT credentials
│   ├── sensors/
│   │   ├── Sensor.h/cpp    ← abstract base class with timed loop() → bool
│   │   ├── DS18B20.h/cpp   ← concrete temperature sensor
│   └── services/
│       ├── MQTTService.h/cpp  ← WiFi + MQTT connection, publish
├── platformio.ini
└── .gitignore
```

### Class design

- **`Sensor`** — abstract base. `loop()` returns `true` only when a fresh read occurred, so `main.cpp` publishes only on new data.
- **`DS18B20`** — reads temperature via DallasTemperature, exposes `getTemperature()`, `getModel()`, and `getRomAddress()`.
- **`MQTTService`** — manages WiFi and MQTT connection, builds the full topic string at publish time. Decoupled from any specific sensor — it receives model and ROM address as arguments.

---

## Dependencies (platformio.ini)

```ini
lib_deps =
  paulstoffregen/OneWire
  milesburton/DallasTemperature
  knolleary/PubSubClient
```
