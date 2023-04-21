/*
  Knock Sensor

  This sketch reads a piezo element to detect a knocking sound.
  It reads an analog pin and compares the result to a set threshold.
  If the result is greater than the threshold, it writes "knock" to the serial
  port, and toggles the LED on pin 13.

  The circuit:
	- positive connection of the piezo attached to analog in 0
	- negative connection of the piezo attached to ground
	- 1 megohm resistor attached from analog in 0 to ground

  created 25 Mar 2007
  by David Cuartielles <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Knock
*/


// these constants won't change:
const int redPin = 9;  // LED connected to digital pin 13
const int bluePin = 11;
const int greenPin = 10;

int redVal = 0;
int blueVal = 0;
int greenVal = 0;
int colorNext = 0; //0 Blue, 1 Red, 3, Green
int waitBuffer = 50;

const int knockSensor = A0;  // the piezo is connected to analog pin 0
const int threshold = 100;   // threshold value to decide when the detected sound is a knock or not
int flag = 0;

// these variables will change:
int sensorReading = 0;  // variable to store the value read from the sensor pin
int ledState = LOW;     // variable used to store the last LED status, to toggle the light
int color = 8;
void ledLight(int pin);

int state = 0; // 0 off, 1 disco on

void setup() {
  pinMode(redPin, OUTPUT);   // declare the ledPin as as OUTPUT
  pinMode(bluePin, OUTPUT);  // declare the ledPin as as OUTPUT
  pinMode(greenPin, OUTPUT);       // declare the ledPin as as OUTPUT
  Serial.begin(115200);         // use the serial port
  flag = 0;
  color = 8;
}

void loop() {
  // read the sensor and store it in the variable sensorReading:
  int sensorReading = analogRead(knockSensor);


  if (sensorReading > 5) {  //sense the vibration the light will gradually light up and change color.
    state = 1;
    // ledLight(RedledPin);
    // ledLight(Green);
    // ledLight(BlueledPin);
  } 
  if (waitBuffer == 0) {
    state = 0;
    waitBuffer = 50;
  }

  if (state == 1) {
    runDisco();
    waitBuffer -= 1;
  } else {
    offDisco();
  }
  analogWrite(greenPin, greenVal);
  analogWrite(redPin, redVal);
  analogWrite(bluePin, blueVal);
  // Serial.print("Colors: ");
  // Serial.print("\n");
  // Serial.print(redVal);
  // Serial.print("\n");
  // Serial.print(blueVal);
  // Serial.print("\n");
  // Serial.print(greenVal);
  // Serial.print("\n");
  // Serial.print("Wait: ");
  // Serial.print("\n");
  // Serial.print(waitBuffer);
  // Serial.print("\n");
  // Serial.print("Vib: ");
  // Serial.print("\n");
  // Serial.print(sensorReading);
  // Serial.print("\n");


  delay(100);  // delay to avoid overloading the serial port buffer
}

// //taper color transition between pins
// void Color(int pina, int pinb) {

//   for (int i = 255; i >= 0; i--) {
//     analogWrite(pina, i);
//     analogWrite(pinb, 255 - i);
//     delay(10);  // waits 10 ms
//   }
// }

void runDisco() {
  if (colorNext == 0) { //green -> blue
    greenVal -= 1;
    blueVal += 1;
    if (greenVal <= 0 || blueVal >= 255) {
      colorNext = 1;
      greenVal = 0;
      blueVal = 255;
    }
  }
  else if (colorNext == 1) { //blue -> red
    blueVal -= 1;
    redVal += 1;
    if (blueVal <= 0 || redVal >= 255) {
      colorNext = 2;
      blueVal = 0;
      redVal = 255;
    }
  }
  else if (colorNext == 2) { //red -> green
    redVal -= 1;
    greenVal += 1;
    if (redVal <= 0 || greenVal >= 255) {
      colorNext = 0;
      redVal = 0;
      greenVal = 255;
    }
  }
}

void offDisco() {
  redVal = 0;
  greenVal = 0;
  blueVal = 0;
}

// void ledLight(int pin) {
//   Serial.print(pin);
//   for (int i = 0; i < 255; i++) {
//     analogWrite(pin, i);
//     delay(10);
//   }
//   for (int i = 254; i >= 0; i--) {
//     analogWrite(pin, i);
//     delay(10);
//   }
// }
