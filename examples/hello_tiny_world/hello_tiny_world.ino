// this code is based on the Blink example
// http://www.arduino.cc/en/Tutorial/Blink

// this sketch cycles through all the possible LED colors

// include all libraries
#include <Inst0.h>
#include <Inst1.h>
#include <Inst2.h>

// constants for time LEDs are on and off
// measured in milliseconds
const int timeOn = 500;
const int timeOff = 250;

// declare instance of the instrument
// default is Inst0, change Inst0 to Inst1 or Inst2 if necessary
Inst0 tiny;

// constant for debugging
// true: the instrument needs to be connected to serial port
// false: the instrument is standalone
const bool tinyDebugging = false;

void setup() {
  tiny.setupInstrument(tinyDebugging);
}

void loop() {

  // turn on and off builtin LED, it is orange
  tiny.setStateLEDBuiltIn(true);
  delay(timeOn);
  tiny.setStateLEDBuiltIn(false);
  delay(timeOff);

  // turn on the RGB LED in all 6 available colors
  tiny.setStateLEDRGB(true, red);
  delay(timeOn);
  tiny.setStateLEDRGB(true, green);
  delay(timeOn);
  tiny.setStateLEDRGB(true, blue);
  delay(timeOn);
  tiny.setStateLEDRGB(true, yellow);
  delay(timeOn);
  tiny.setStateLEDRGB(true, magenta);
  delay(timeOn);
  tiny.setStateLEDRGB(true, cyan);
  delay(timeOn);

  // turn off the RGB LED, color is irrelevant
  tiny.setStateLEDRGB(false, red);
  delay(timeOff);
}
