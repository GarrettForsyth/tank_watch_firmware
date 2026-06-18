#include "PhCalibration.h"
#include <Preferences.h>
#include <services/NvsConfig.h>

// Default approximations for the board on 3.3V supply.
// - Midpoint: 2.5V at pH 7 (electrode isopotential point, independent of supply voltage)
// - Slope: ~-5.5 pH/V (output decreases as pH increases)
// - Offset: 21.34 (derived from: 7 = -5.5 * 2.5 + offset)
constexpr const float DEFAULT_SLOPE = -5.5;
constexpr const float DEFAULT_OFFSET = 21.34;

constexpr const char* KEY_SLOPE = "ph_slope";
constexpr const char* KEY_OFFSET = "ph_offset";

PhCalibration getOrDefaultPhCalibration() {
    Preferences prefs;
    prefs.begin(NVS_NAME_SPACE, true); // Read only

    PhCalibration calibration;
    calibration.slope = prefs.getFloat(KEY_SLOPE, DEFAULT_SLOPE);
    calibration.offset = prefs.getFloat(KEY_OFFSET, DEFAULT_OFFSET);

    prefs.end();
    return calibration;
}

void savePhCalibration(float slope, float offset) {
    Preferences prefs;
    prefs.begin(NVS_NAME_SPACE, false);

    prefs.putFloat(KEY_SLOPE, slope);
    prefs.putFloat(KEY_OFFSET, offset);

    prefs.end();
}