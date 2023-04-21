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
const int RedledPin = 9;       // LED connected to digital pin 13
const int BlueledPin = 11;
const int Green = 10;
const int knockSensor = A0;  // the piezo is connected to analog pin 0
const int threshold = 100;   // threshold value to decide when the detected sound is a knock or not
int flag = 0;

// these variables will change:
int sensorReading = 0;  // variable to store the value read from the sensor pin
int ledState = LOW;     // variable used to store the last LED status, to toggle the light
int color = 8;
void ledLight(int pin);
void setup() {
  pinMode(RedledPin, OUTPUT);  // declare the ledPin as as OUTPUT
  pinMode(BlueledPin, OUTPUT);  // declare the ledPin as as OUTPUT
  pinMode(Green, OUTPUT);  // declare the ledPin as as OUTPUT
  Serial.begin(115200);       // use the serial port
  flag = 0;
  color = 8;
}

void loop() {
  // read the sensor and store it in the variable sensorReading:
  int sensorReading = analogRead(knockSensor);
  
  
  if (sensorReading > 5 ) { //sense the vibration the light will gradually light up and change color.
    
    ledLight(RedledPin);
    ledLight(Green);
    ledLight(BlueledPin);
  } 
  /*else if(sensorReading > 5 && flag == 1){
    flag = 0;
    digitalWrite(Green, LOW);
  }*/
  //Serial.print(sensorReading);
  delay(100);  // delay to avoid overloading the serial port buffer
}

void ledLight(int pin){
  Serial.print(pin);
  for(int i=0;i<255;i++){
    analogWrite(pin, i);
    delay(10);
  }
  for(int i=254; i>=0 ;i--){
    analogWrite(pin, i);
    delay(10);
  }
}

