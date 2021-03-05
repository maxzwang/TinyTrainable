/// @file hello_tiny_world.ino
/// @brief Test output modes
/// @author montoyamoraga, peter-parque, maxzwang
/// @date March 2021

// include main library
#include <TinyTrainable.h>

// declare instance of instrument
TinyTrainable tiny;

// output mode to test, other possible values:
// outputLED, outputMIDI, outputSerialUSB
OutputMode outputToTest = outputBuzzer;

// hardware constants
const int outputPin = 8;

// setup() runs once, at the beginning
void setup() {
  // setup the test
  tiny.helloOutputsSetup(outputToTest, outputPin);
}

// loop() runs in a loop, after setup()
void loop() {
  // test the output
  tiny.helloOutputs(outputToTest);
}