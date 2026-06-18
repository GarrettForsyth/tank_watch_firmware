/**
 * Filename: PhCalibration.cpp
 * Author: Garrett Forsyth
 * Date: June 16 2026
 * Description: Structure used to store pH calibration.
 * 
 * pH Calibration is stored in preferences to survive reboots.
 */
#pragma once


struct PhCalibration {
    float slope;
    float offset;
};

PhCalibration getOrDefaultPhCalibration();

void savePhCalibration(float slopw, float offset);