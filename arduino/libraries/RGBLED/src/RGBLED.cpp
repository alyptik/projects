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
Contains the RGBLED class definition.
*/

#include "RGBLED.hpp"
#include "RGBLED_debug.hpp"

RGBLED::RGBLED(uint8_t red_pin, uint8_t green_pin, uint8_t blue_pin, CommonElectrode commonElectrode)
  : _red(red_pin), _green(green_pin), _blue(blue_pin),
    _commonElectrode(commonElectrode), _brightness(255), _state(ON) {
  pinMode(_red.pin, OUTPUT);
  pinMode(_green.pin, OUTPUT);
  pinMode(_blue.pin, OUTPUT);
  digitalWrite(_red.pin, (bool)_commonElectrode);
  digitalWrite(_green.pin, (bool)_commonElectrode);
  digitalWrite(_blue.pin, (bool)_commonElectrode);
}

void RGBLED::on() { RGBLED_DEBUG(F("Setting state to ON")); _state = ON; }

void RGBLED::off() { RGBLED_DEBUG(F("Setting state to OFF")); _state = OFF; }

State RGBLED::state() const { return _state; }


uint8_t RGBLED::brightness() const {
  return round(_brightness * PWM_MAX);
}

void RGBLED::brightness(uint8_t brightnessValue) {
  RGBLED_DEBUG(F("RGBLED: Setting brightness to ")); RGBLED_DEBUGLN(brightnessValue);
  static uint8_t brightnessValue_last = 0;
  if (brightnessValue_last == brightnessValue) return;
  brightnessValue_last = brightnessValue;
  _brightness = (float)brightnessValue / (float)PWM_MAX;
  recalculate_total_correction();
}

void RGBLED::operator()(uint8_t brightnessValue) {
  brightness(brightnessValue);
}


uint8_t RGBLED::red() const { return _red.value; }

void RGBLED::red(uint8_t redValue) {
  RGBLED_DEBUG(F("RGBLED: setting red to ")); RGBLED_DEBUGLN(redValue);
  _red.value = redValue;
}

uint8_t RGBLED::green() const { return _green.value; }

void RGBLED::green(uint8_t greenValue) {
  RGBLED_DEBUG(F("RGBLED: setting green to ")); RGBLED_DEBUGLN(greenValue);
  _green.value = greenValue;
}

uint8_t RGBLED::blue() const { return _blue.value; }

void RGBLED::blue(uint8_t blueValue) {
  RGBLED_DEBUG(F("RGBLED: setting blue to ")); RGBLED_DEBUGLN(blueValue);
  _blue.value = blueValue;
}

void RGBLED::operator()(uint8_t redValue, uint8_t greenValue, uint8_t blueValue) {
  red(redValue);
  green(greenValue);
  blue(blueValue);
}

uint8_t RGBLED::red_correction() const {
  return round(_red.correction * PWM_MAX);
}

void RGBLED::red_correction(uint8_t red_correction) {
  RGBLED_DEBUG(F("RGBLED: Setting red correction to ")); RGBLED_DEBUGLN(red_correction);
  _red.correction = (float)red_correction / (float)PWM_MAX;
  recalculate_total_correction();
}

uint8_t RGBLED::green_correction() const {
  return round(_green.correction * PWM_MAX);
}

void RGBLED::green_correction(uint8_t green_correction) {
  RGBLED_DEBUG(F("RGBLED: Setting green correction to ")); RGBLED_DEBUGLN(green_correction);
  _green.correction = (float)green_correction / (float)PWM_MAX;
  recalculate_total_correction();
}

uint8_t RGBLED::blue_correction() const {
  return round(_blue.correction * PWM_MAX);
}

void RGBLED::blue_correction(uint8_t blue_correction) {
  RGBLED_DEBUG(F("RGBLED: Setting blue correction to ")); RGBLED_DEBUGLN(blue_correction);
  _blue.correction = (float)blue_correction / (float)PWM_MAX;
  recalculate_total_correction();
}


void RGBLED::show(bool force) const {
  RGBLED_DEBUG(F("RGBLED: writing - "));

  if (_state == OFF) {
    digitalWrite(_red.pin, (bool)_commonElectrode);
    digitalWrite(_green.pin, (bool)_commonElectrode);
    digitalWrite(_blue.pin, (bool)_commonElectrode);
    return;
  }

  RGBLED_DEBUG(F("red: ")); RGBLED_DEBUG(round((float)_red.value * _red.total_correction));
  static uint16_t redValue_last = 0;
  static uint16_t redCorrection_last = 0;
  if (_red.value != redValue_last || _red.total_correction != redCorrection_last || force) {
    if (_commonElectrode == CommonElectrode::cathode) {
      analogWrite(_red.pin, round((float)_red.value * _red.total_correction));
    } else {
      analogWrite(_red.pin, PWM_MAX - round((float)_red.value * _red.total_correction));
    }
    redValue_last = _red.value;
    redCorrection_last = _red.total_correction;
  }

  RGBLED_DEBUG(F(", green: ")); RGBLED_DEBUG(round((float)_green.value * _green.total_correction));
  static uint16_t greenValue_last = 0;
  static uint16_t greenCorrection_last = 0;
  if (_green.value != greenValue_last || _green.total_correction != greenCorrection_last || force) {
    if (_commonElectrode == CommonElectrode::cathode) {
      analogWrite(_green.pin, round((float)_green.value * _green.total_correction));
    } else {
      analogWrite(_green.pin, PWM_MAX - round((float)_green.value * _green.total_correction));
    }
    greenValue_last = _green.value;
    greenCorrection_last = _green.total_correction;
  }

  RGBLED_DEBUG(F(", blue: ")); RGBLED_DEBUGLN(round((float)_blue.value * _blue.total_correction));
  static uint16_t blueValue_last = 0;
  static uint16_t blueCorrection_last = 0;
  if (_blue.value != blueValue_last || _blue.total_correction != blueCorrection_last || force) {
    if (_commonElectrode == CommonElectrode::cathode) {
      analogWrite(_blue.pin, round((float)_blue.value * _blue.total_correction));
    } else {
      analogWrite(_blue.pin, PWM_MAX - round((float)_blue.value * _blue.total_correction));
    }
    blueValue_last = _blue.value;
    blueCorrection_last = _blue.total_correction;
  }
}

void RGBLED::recalculate_total_correction() {
  RGBLED_DEBUG(F("RGBLED: recalculating total correction - "));
  _red.total_correction = _red.correction * _brightness;
  RGBLED_DEBUG(F("red: ")); RGBLED_DEBUG(_red.total_correction);
  _green.total_correction = _green.correction * _brightness;
  RGBLED_DEBUG(F(", green: ")); RGBLED_DEBUG(_green.total_correction);
  _blue.total_correction = _blue.correction * _brightness;
  RGBLED_DEBUG(F(", blue: ")); RGBLED_DEBUGLN(_blue.total_correction);
}
