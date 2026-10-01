/*
  Adafruit Feather ESP32 v2
  Controls 10 LEDs using 2 pressure sensors
  - 0 sensors pressed -> Off (0)
  - 1 sensor pressed  -> Half brightness (90)
  - 2 sensors pressed -> Full brightness (255)
*/

// analog input pins on the Feather ESP32 (Pins A2 and A3)
const int sensor1Pin = A2; 
const int sensor2Pin = A3; 

// 4 pins driving the 10 LEDs
const int ledPins[4] = {13, 12, 27, 33}; 
const int numPins = 4;

// pressure detection threshold
const int pressureThreshold = 2000; 

const int brightnessOff = 0;
const int brightnessHalf = 90;   // 50% brightness
const int brightnessFull = 255;  // 100% brightness

void setup() {
  Serial.begin(9600);

  // configure LED pins as outputs
  for (int i = 0; i < numPins; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // read ADC values (0 - 4095)
  int sensor1Value = analogRead(sensor1Pin);
  int sensor2Value = analogRead(sensor2Pin);

  bool isSensor1Pressed = (sensor1Value >= pressureThreshold);
  bool isSensor2Pressed = (sensor2Value >= pressureThreshold);

  int ledValue = brightnessOff;

  // determine brightness based on how many sensors are triggered
  if (isSensor1Pressed && isSensor2Pressed) {
    ledValue = brightnessFull; // two sensors pressed -> Full brightness
  } else if (isSensor1Pressed || isSensor2Pressed) {
    ledValue = brightnessHalf; // one sensor pressed -> Half brightness
  } else {
    ledValue = brightnessOff;  // zero pressure pressed -> Turn off
  }

  // write PWM signal to all target GPIO pins
  for (int i = 0; i < numPins; i++) {
    analogWrite(ledPins[i], ledValue);
  }

  // debugging output for the Serial Monitor
  Serial.print("S1: ");
  Serial.print(sensor1Value);
  Serial.print(" | S2: ");
  Serial.print(sensor2Value);
  Serial.print(" -> LED Value: ");
  Serial.println(ledValue);

  delay(20);
}