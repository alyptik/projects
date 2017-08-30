/*
The MIT License (MIT)

Copyright (c) 2016 Vasil Kalchev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
@file
Include file for RGBLED library.

@author Vasil Kalchev
@date 2017
@version 1.0.0
@copyright The MIT License
*/

#pragma once

#include <inttypes.h>
#include <math.h>
#include <Arduino.h>

/// Common electrode enum.
enum class CommonElectrode : bool {
  anode = 1, cathode = 0,
};

/// State enum.
enum State : bool {
  ON = 1, OFF = 0,
};

/// The maximum value of the PWM
const uint8_t PWM_MAX = 255;


class RGBLED {
public:
  /// The class constructor.
  /**
  @param red_pin - the pin connected to red
  @param green_pin - the pin connected to green
  @param blue_pin - the pin connected to blue
  @param commonElectrode - specifies the LED's common electrode
  */
  RGBLED(uint8_t red_pin, uint8_t green_pin, uint8_t blue_pin, CommonElectrode commonElectrode = CommonElectrode::cathode);

  /// Turns the LED ON
  void on();

  /// Turns the LED OFF
  void off();

  /// Returns the state of the LED
  /**
  @returns the state of the LED

  @see State
  */
  State state() const;

  /// Returns the brightness of the LED
  /**
  @returns the brightness of the LED
  */
  uint8_t brightness() const;

  /// Sets the LED's brightness
  /**
  @param brightness - the brightness value
  */
  void brightness(uint8_t brightness);
  /// Sets the LED's brightness
  /**
  @param brightness - the brightness value

  @see void RGBLED::brightness(uint8_t brightness)
  */
  void operator()(uint8_t brightness);

  /// Returns the red value
  /**
  @returns the red value
  */
  uint8_t red() const;
  /// Sets the red value
  /**
  @param redValue - the red value
  */
  void red(uint8_t redValue);
  /// Returns the green value
  /**
  @returns the green value
  */
  uint8_t green() const;
  /// Sets the green value
  /**
  @param greenValue - the green value
  */
  void green(uint8_t greenValue);
  /// Returns the blue value
  /**
  @returns the blue value
  */
  uint8_t blue() const;
  /// Sets the blue value
  /**
  @param blueValue - the blue value
  */
  void blue(uint8_t blueValue);
  /// Sets the RGB values simultaneously
  /**
  @param redValue - the red value
  @param greenValue - the green value
  @param blueValue - the blue value
  */
  void operator()(uint8_t redValue, uint8_t greenValue, uint8_t blueValue);

  /// Returns the red correction
  /**
  @returns the red correction
  */
  uint8_t red_correction() const;
  /// Sets the red correction
  /**
  @param red_correction - the red correction
  */
  void red_correction(uint8_t red_correction);
  /// Returns the green correction
  /**
  @returns the green correction
  */
  uint8_t green_correction() const;
  /// Sets the green correction
  /**
  @param green_correction - the green correction
  */
  void green_correction(uint8_t green_correction);
  /// Returns the blue correction
  /**
  @returns the blue correction
  */
  uint8_t blue_correction() const;
  /// Sets the blue correction
  /**
  @param blue_correction - the blue correction
  */
  void blue_correction(uint8_t blue_correction);

  /// Updates the LEDs with the current settings
  /**
  @param force - forces the update (otherwise update could be skipped if there wasn't a change)
  */
  void show(bool force = false) const;

private:
  void recalculate_total_correction();
  struct Channel {
    explicit Channel(uint8_t pin) : pin(pin), value(0), value_last(0), correction(1), total_correction(1) {}
    const uint8_t pin;
    uint8_t value;
    uint8_t value_last;
    float correction;
    float total_correction;
  };
  Channel _red;
  Channel _green;
  Channel _blue;
  CommonElectrode _commonElectrode;
  float _brightness;
  State _state;
};
