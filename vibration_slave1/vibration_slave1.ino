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


//Slave1
#include <Wire.h>
const int sensorNum = 1; //number of sensor&LED set
//const int LEDPins[sensorNum][3] = {{5, 6, 7}, {8, 9, 10}, {11, 12, 13}}; //led pin ports
const int LEDPins[sensorNum][3] = {{5, 6, 7}};
//const int LEDPins[sensorNum][3] = {{5,6,7}};

int LEDvalue[sensorNum][3]; //0 red, 1 green, 2 blue
int colorNext[sensorNum]; //0 Blue, 1 Red, 2 Green
int waitBuffer[sensorNum];


//const int knockSensor[sensorNum] = {A0, A1, A2};  // the piezo is connected to analog pin 0
const int knockSensor[sensorNum] = {A0}; 
const int threshold = 20;   // threshold value to decide when the detected sound is a knock or not
int flag = 0;

// these variables will change:
int sensorReading[sensorNum];  // variable to store the value read from the sensor pin
int ledState = LOW;     // variable used to store the last LED status, to toggle the light
int color = 8;


//byte arbitraryCode[sensorNum] = {97, 98, 99}; //music 
byte arbitraryCode[sensorNum] = {97};
int state[sensorNum]; // 0 off, 1 disco on

void initialize() {
  for (int i=0;i<sensorNum;i++){
    for (int j=0;j<3;j++) {
      pinMode(LEDPins[i][j], OUTPUT);
      LEDvalue[i][j] = 0;
    }
    colorNext[i] = 0;
    waitBuffer[i] = 50;
    state[i] = 0;
    sensorReading[i] = 0;
  }
  //return ;
}

void setup() {
  initialize();
  //Wire.begin();
  Wire.begin(9); 
  Serial.begin(9600);         // use the serial port
  //Wire.onReceive(receiveEvent);
}

void requestEvent()
{
  Wire.write(state[0]);
}

void loop() {
  // read the sensor and store it in the variable sensorReading:
  for(int i=0;i<sensorNum;i++){
    sensorReading[i] = analogRead(knockSensor[i]); 
    
  }
  Serial.println(sensorReading[0]);

  for(int i=0;i<sensorNum;i++){
    if(sensorReading[i] > threshold) { 
      if(state[i] == 0) { //if the light is low and light up again we'll turn on the music
        Serial.write(arbitraryCode[0]);
      } 
      state[i] = 1;

    }
  }
  
  /*
  transmit status to master
  */
  Wire.onRequest(requestEvent);

  for (int i=0;i<sensorNum;i++){
    changeLightStatus(i);
  }

  changeLightColor(0);
  changeLightColor(1);
  changeLightColor(2);

  delay(100);  // delay to avoid overloading the serial port buffer
}

/*void transmitData2Slave(int slave, int val) {
  Wire.beginTransmission(slave);
  Wire.write(val);              // sends val 
  Wire.endTransmission();    // stop transmitting
}*/

void changeLightStatus(int idx) { //check light status and wait buffer
  if(waitBuffer[idx] == 0) {
    state[idx] = 0;
    waitBuffer[idx] = 50;
  }
  if(state[idx] == 1){
    runDisco(idx);
    waitBuffer[idx] -= 1;
  }
  else {
    offDisco(idx);
  }
}
void changeLightColor(int idx) { //analogwrite for led color
  analogWrite(LEDPins[idx][1], LEDvalue[idx][1]);
  analogWrite(LEDPins[idx][0], LEDvalue[idx][0]);
  analogWrite(LEDPins[idx][2], LEDvalue[idx][2]);
}

void runDisco(int idx) { //color changes
  if (colorNext[idx] == 2) { //green -> blue
    LEDvalue[idx][1] -= 1; 
    LEDvalue[idx][2] += 1;
    if (LEDvalue[idx][1] <= 0 || LEDvalue[idx][2] >= 255) {
      colorNext[idx] = 1;
      LEDvalue[idx][1] = 0;
      LEDvalue[idx][2] = 255;
    }
  }
  else if (colorNext[idx] == 0) { //blue -> red
    LEDvalue[idx][2] -= 1;
    LEDvalue[idx][0] += 1;
    if (LEDvalue[idx][2] <= 0 || LEDvalue[idx][0] >= 255) {
      colorNext[idx] = 2;
      LEDvalue[idx][2] = 0;
      LEDvalue[idx][0] = 255;
    }
  }
  else if (colorNext[idx] == 1) { //red -> green
    LEDvalue[idx][0] -= 1;
    LEDvalue[idx][1] += 1;
    if (LEDvalue[idx][0] <= 0 || LEDvalue[idx][1] >= 255) {
      colorNext[idx] = 0;
      LEDvalue[idx][0] = 0;
      LEDvalue[idx][1] = 255;
    }
  }
}

void offDisco(int idx) {
  LEDvalue[idx][0] = 0;
  LEDvalue[idx][1] = 0;
  LEDvalue[idx][2] = 0;
}
