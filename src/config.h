/**
 * Filename: config.h
 * Author: Garrett Forsyth
 * Date: May 1 2026
 * Description: Configuration parameters to use.
 * 
 * Note: This will depend on how the board is wired.
 */
#pragma once

#define DS18B20_GPIO_PIN 4

// TODO: In the future, we could hae more resolved
// read intervals (e.g. each sensor could be configured)
#define DEFAULT_READ_INTERVAL 3000