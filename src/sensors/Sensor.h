/**
 * Filename: Sensor.h
 * Author: Garrett Forsyth
 * Date: May 1 2026
 * Description: This file contains declarations for the abstract sensor class.
 * 
 * Sensors need to be initialized in begin()
 * Their readings are read in read()
 * How often they are read is determined by interval and lastRead
 */
#pragma once
#include "config.h"

class Sensor {
public:
    /**
     * Executes any sensor initialization logic.
     */
    virtual void begin() = 0;

    /**
     * Triggers a sensor read.
     * The frequency is determined by [interval] and [lastRead]
     */
    virtual void read() = 0;

    /**
     * Called during program loop. Checks if it is time
     * to read the sensor data and if so does.
     * 
     * Returns bool: true if a value was read; false otherwise
     */
    bool loop();

    /**
     * Gets a string of the model name of the sensor.
     */
    virtual const char* getModel() = 0;

    /**
     * Get's a unique identifer for the sensor.
     * (Ex/ ROM address or hardware ID)
     */
    virtual const char* getId() = 0;

    /**
     * Deconstructor for children to chain call.
     */
    virtual ~Sensor() {};

protected:
    /**
     * The time interval, in millis, in which the sensor
     * should be read.
     */
    unsigned long interval = DEFAULT_READ_INTERVAL;

    /**
     * The millis time from epoch the sensor was last read. 
     */
    unsigned long lastRead = 0;
};