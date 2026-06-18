// SensorIdentity.cpp
#include "SensorIdentity.h"
#include "config.h"
#include <Preferences.h>
#include "services/NvsConfig.h"

const char* getOrCreateSensorId(const char* model, uint8_t gpio) {
    static char id[MAX_VALUE_LENGTH];

    // Key is of form '{model}_{gpio}'
    char key[MAX_KEY_LENGTH];
    snprintf(key, sizeof(key), "%s_%d", model, gpio);

    Preferences prefs;
    prefs.begin(NVS_NAME_SPACE, false);

    if (prefs.isKey(key)) {
        prefs.getString(key, id, sizeof(id));
    } else {
        // Create a UUID by generating 4 random numbers in hex (include padding)
        snprintf(
            id,
             sizeof(id),
              "%08lx%08lx%08lx%08lx",
            esp_random(), esp_random(), esp_random(), esp_random()
        );
        prefs.putString(key, id);
    }

    prefs.end();
    return id;
}