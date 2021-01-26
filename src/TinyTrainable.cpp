// include local library
#include "TinyTrainable.h"

// constructor for the TinyTrainable class
TinyTrainable::TinyTrainable() {

}

void TinyTrainable:: setupLEDs() {
  // setting up orange built-in LED
  pinMode(LED_BUILTIN, OUTPUT);
  // initial state off is HIGH for on
  digitalWrite(LED_BUILTIN, HIGH);
  
  // setting up RGB LED
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  // default state off is HIGH
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
}

// function for turning on and off the built-in LED
void TinyTrainable::setStateLEDBuiltIn(bool turnOn) {
  if (turnOn) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void TinyTrainable::blinkLEDBuiltIn(int blinks) {

  setStateLEDBuiltIn(false);

  for (int i = 0; i < blinks; i++) {
    setStateLEDBuiltIn(true);
    delay(500);
    setStateLEDBuiltIn(false);
    delay(500);
  }
}

// function for turning on and off the RGB LED
void TinyTrainable::setStateLEDRGB(bool turnOn, Colors color) {
  
  // first turn off
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);

  // then turn on according to color
  if (turnOn) {
    switch (color) {
      case red:
        digitalWrite(LEDR, LOW);
        break;
      case green:
        digitalWrite(LEDG, LOW);
        break;
      case blue:
        digitalWrite(LEDB, LOW);
        break;
      case yellow:
        digitalWrite(LEDR, LOW);
        digitalWrite(LEDG, LOW);
        break;
      case magenta:
        digitalWrite(LEDR, LOW);
        digitalWrite(LEDB, LOW);
        break;
      case cyan:
        digitalWrite(LEDG, LOW);
        digitalWrite(LEDB, LOW);
        break;
    }
  }
}

// traps the arduino in an infinite loop with RGB LED blinking, to signal 
// some setup missing. explanations in docs by instrument.
void TinyTrainable::errorBlink(Colors color, int blinkNum) {
  while (true) {
    for (int i = 0; i <= blinkNum; i++) {
      // turn on with the color
      setStateLEDRGB(true, color);
      delay(1000);
      // turn off
      setStateLEDRGB(false, color);
      delay(1000);
    }
    blinkLEDBuiltIn(1);
  }
}

// APDS9960 sensor for gestures, color, light intensity, proximity 
void TinyTrainable::setupSensorAPDS9960() {
    if (!APDS.begin()) {
    while (1);
  }
}

// include library for temperature and humidity sensor
// https://www.arduino.cc/en/Reference/ArduinoHTS221
void TinyTrainable::setupSensorHTS221() {
    if (!HTS.begin()) {
    while (1);
  }
}

// include library for pressure sensor
// https://www.arduino.cc/en/Reference/ArduinoLPS22HB/
void TinyTrainable::setupSensorLPS22HB() {
    if (!BARO.begin()) {
    while (1);
  }
}

// LSM9DS1 sensor for IMU (inertial measurement unit)
//  3-axis accelerometer, gyroscope, magnetometer
void TinyTrainable::setupSensorLSM9DS1() {
  if (!IMU.begin()) {
    while(1);
  }
}

void TinyTrainable::setupOutputBuzzer(int outputPin, int buzzerDuration, int freq0, int freq1, int freq2) {
  _outputMode = outputBuzzer;
  _outputPinBuzzer = outputPin;
  pinMode(_outputPinBuzzer, OUTPUT);
  _buzzerDuration = buzzerDuration;

  _buzzerFrequencies[0] = freq0;
  _buzzerFrequencies[1] = freq1;
  _buzzerFrequencies[2] = freq2;
}

void TinyTrainable::setupOutputMIDI(byte midiChannel, byte midiVelocity, int note0, int note1, int note2) {
  _outputMode = outputMIDI;
  _midiChannel = midiChannel;
  _midiVelocity = midiVelocity;

  _midiNotes[0] = note0;
  _midiNotes[1] = note1;
  _midiNotes[2] = note2;

  setupSerialMIDI();
}

void TinyTrainable::setupOutputSerialUSB() {
  _outputMode = outputSerialUSB;

  Serial.begin(9600);
  while (!Serial);
}

void TinyTrainable::setupOutputServo(int outputPin, int angle0, int angle1, int angle2) {
  _outputPinServo = outputServo;
  pinMode(_outputPinServo, OUTPUT);

  _servoAngles[0] = angle0;
  _servoAngles[1] = angle1;
  _servoAngles[2] = angle2;
}

// void TinyTrainable::setServoAngle(int angle) {
//   if (_servoAngleCurrent < angle) {
//     for (int i = _servoAngleCurrent; i < angle; i++) {
//       _servo.write(i);
//       delay(15);
//     }
//   }
//   else {
//     for (int i = _servoAngleCurrent; i > angle; i--) {
//       _servo.write(i);
//       delay(15);
//     }
//   }
// }

// sets up Serial MIDI output on TX pin
void TinyTrainable::setupSerialMIDI() {

  // open serial tranmission on TX pin
  Serial1.begin(9600);

  // desired baudrate for MIDI
  uint32_t baudrate = 0x800000;

  // declare pointer to the memory address that stores the baudrate
  uint32_t *pointerBaudrate = ( uint32_t * )0x40002524;

  // replace the value at the pointer with the desired baudrate
  *pointerBaudrate = baudrate;
}

void TinyTrainable::sendSerialMIDINote(byte channel, byte note, byte velocity) {
  Serial1.write(143 + channel);
  Serial1.write(note);
  Serial1.write(velocity);
}
