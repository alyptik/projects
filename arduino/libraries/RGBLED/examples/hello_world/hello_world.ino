/*
 * RGBLED library - hello_menu.ino
 *
 * This example demonstrates the usage of different methods
 * of the RGBLED class.
 *
 * The circuit:
 * RGB LED (common cathode):
 * - red pin to Arduino pin 3
 * - green pin to Arduino pin 5
 * - blue pin to Arduino pin 6
 * - ---
 * RGB LED strip (common anode):
 * - red pin control to Arduino pin 9
 * - green pin control to Arduino pin 10
 * - blue pin control to Arduino pin 11
 * *An LED strip requires additional components
 *
 * Created May 4, 2017
 * by Vasil Kalchev
 *
 * https://github.com/VasilKalchev/RGBLED
 *
 */

#include "RGBLED.hpp"

const unsigned int fade_period = 100;

// Pin mapping for the first RGBLED object:
const byte redLed = 3;
const byte greenLed = 5;
const byte blueLed = 6;
// The RGBLED object defaults to common cathode configuration.
RGBLED rgbLed(redLed, greenLed, blueLed);

// Pin mapping for the second RGBLED object:
const byte redStrip = 9;
const byte greenStrip = 10;
const byte blueStrip = 11;
// To specify the common electrode use the 'CommonElectrode' enum class.
RGBLED rgbStrip(redStrip, greenStrip, blueStrip, CommonElectrode::anode);


void setup() {
  Serial.begin(250000);
  Serial.println("RGBLED 'hello_world' example.");

  // Turns ON/OFF the leds.
  rgbLed.on();
  rgbStrip.off();

  // Sets the brightness.
  rgbLed.brightness(PWM_MAX);
  // Sets PWM for a color
  rgbLed.red(255); rgbLed.green(255); rgbLed.blue(0);
  // The method 'RGBLED::show()' must be called to execute the changes.
  rgbLed.show();
  rgbStrip.show();

  delay(2000);

  rgbLed.off();
  rgbStrip.on();

  rgbStrip(PWM_MAX / 2);
  // The individual colors can be color corrected.
  rgbStrip.red_correction(255);
  rgbStrip.green_correction(176);
  rgbStrip.blue_correction(240);
  // This is alternative to individually setting the PWM values of the colors
  /* Because green is color corrected, setting green
   * to 255 will actually set it to 176 in this case.
   */
  rgbStrip(255, 255, 0);
  rgbLed.show();
  rgbStrip.show();

  delay(2000);

  rgbLed.off();
  rgbStrip.off();
  rgbLed.show();
  rgbStrip.show();

  delay(500);

  rgbLed.on();
  rgbStrip.on();
  rgbLed.show();
  rgbStrip.show();
}

void loop() {
  rgbLed.show();
  rgbStrip.show();

  static uint32_t millis_last = 0;
  if (millis() > millis_last + fade_period) {
    millis_last = millis();
    uint8_t brightness = rgbLed.brightness();
    if (brightness > 0) {
      rgbLed.brightness(--brightness);
      rgbStrip.brightness(--brightness);
      Serial.print("Setting brightness to "); Serial.println(brightness);
    }
  }
}
