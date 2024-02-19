RGBLED
======

*Arduino library for easy control of RGB LEDs.*

[![Build Status](https://travis-ci.org/VasilKalchev/RGBLED.svg?branch=master)](https://travis-ci.org/VasilKalchev/RGBLED)
[![release](https://img.shields.io/badge/release-1.0.0-yellow.svg)](https://github.com/VasilKalchev/RGBLED/releases)
[![documentation](https://img.shields.io/badge/docs-doxygen-green.svg)](https://vasilkalchev.github.io/RGBLED/doc/Doxygen/html/index.html)
[![license](https://img.shields.io/github/license/mashape/apistatus.svg?maxAge=2592000)](https://opensource.org/licenses/mit-license.php)

Set the color with one function, turn LEDs ON/OFF, set the brightness, set color correction and get the current state of the object.


Resources
=========
 - [Examples][examples]
 - [API reference][doxygen classes]
 - [Latest release][latest release]


Features
========
 - Easy control of RGB LEDs.
 - Adjustable brightness.
 - Color correction.
 - State information.


Quick start
===========
To create an object specify the pins of the RGB LED:
```c++
RGBLED rgbLed(3, 5, 6);
```


The RGBLED constructor defaults to common cathode. To specify the common electrode use the 'CommonElectrode' enum class:
```c++
RGBLED rgbLed1(3, 5, 6, CommonElectrode::anode);
RGBLED rgbLed2(9, 10, 11, CommonElectrode::cathode);
```


Setting the color:
```c++
rgbLed.red(127);
rgbLed.green(0);
rgbLed.blue(127);

// or

rgbLed(127, 0, 127);
```


Setting the brightness:
```c++
rgbLed.brightness(80);

// or

rgbLed(80);
```


Turning the LED ON/OFF:
```c++
rgbLed.on();
rgbLed.off();
```


Color correction:
```c++
rgbLed.red_correction(255);
rgbLed.green_correction(176);
rgbLed.blue_correction(240);
```


Getting the state of the object:
```c++
Serial.print("Brightness: "); Serial.println(rgbLed.brightness());
Serial.print("State: "); Serial.println(rgbLed.state());
Serial.print("Red value: "); Serial.println(rgbLed.red());
Serial.print("Green value: "); Serial.println(rgbLed.green());
Serial.print("Blue value: "); Serial.println(rgbLed.blue());
Serial.print("Red correction value: "); Serial.println(rgbLed.red_correction());
Serial.print("Green correction value: "); Serial.println(rgbLed.green_correction());
Serial.print("Blue correction value: "); Serial.println(rgbLed.blue_correction());
```


License
=======
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


[doxygen classes]: https://vasilkalchev.github.io/RGBLED/doc/Doxygen/html/annotated.html
[examples]: https://github.com/VasilKalchev/RGBLED/tree/master/examples
[latest release]: https://github.com/VasilKalchev/RGBLED/releases/latest
