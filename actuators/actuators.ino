#include <Servo.h>    // Instead of directly changing the PWM value,
                     // we'll use Servo library
Servo myservo; 

//the right motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;  //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;  //control pin 2 on the motor driver for the right motor
const int PWMA = 11;  //speed control pin on the motor driver for the right motor

//the left motor will be controlled by the motor B pins on the motor driver
const int PWMB = 3;  //speed control pin on the motor driver for the left motor
const int BIN2 = 2;   //control pin 2 on the motor driver for the left motor
const int BIN1 = 4;   //control pin 1 on the motor driver for the left motor

int switchPin = 7;  //switch to turn the robot on and off

int waitBuffer = 5;
int angle = 0;
bool incAngle = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(switchPin, INPUT_PULLUP);  //set this as a pullup to sense whether the switch is flipped

  //set the motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  myservo.attach(5);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(7));
  if (incAngle && angle > 6) {
    angle = 6;
    incAngle = false;
  } else if (incAngle) {
    angle += 1;
  } else if (angle < 0) {
    angle = 0;
    incAngle = true;
  } else {
    angle -= 1;
  }
  myservo.write(angle * 30);
  if (digitalRead(7) == 1) {
    if (waitBuffer != 0) {

      rightMotor(-500);
      leftMotor(500);
      

      waitBuffer -= 1;
      Serial.println(waitBuffer);
      

    } else {
      rightMotor(0);  //turn the right motor off
      leftMotor(0);
      waitBuffer -= 1;
      if (waitBuffer < -5) {
        waitBuffer = 5;
      }
    }
  } else {
    rightMotor(0);  //turn the right motor off
    leftMotor(0);
  }
  delay(1000);
}

void rotateBase() {

}

void rightMotor(int motorSpeed)  //function for driving the right motor
{
  if (motorSpeed > 0)  //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);  //set pin 1 to high
    digitalWrite(AIN2, LOW);   //set pin 2 to low
  } else if (motorSpeed < 0)   //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);   //set pin 1 to low
    digitalWrite(AIN2, HIGH);  //set pin 2 to high
  } else                       //if the motor should stop
  {
    digitalWrite(AIN1, LOW);  //set pin 1 to low
    digitalWrite(AIN2, LOW);  //set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed));  //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
void leftMotor(int motorSpeed)  //function for driving the left motor
{
  if (motorSpeed > 0)  //if the motor should drive forward (positive speed)
  {
    digitalWrite(BIN1, HIGH);  //set pin 1 to high
    digitalWrite(BIN2, LOW);   //set pin 2 to low
  } else if (motorSpeed < 0)   //if the motor should drive backward (negative speed)
  {
    digitalWrite(BIN1, LOW);   //set pin 1 to low
    digitalWrite(BIN2, HIGH);  //set pin 2 to high
  } else                       //if the motor should stop
  {
    digitalWrite(BIN1, LOW);  //set pin 1 to low
    digitalWrite(BIN2, LOW);  //set pin 2 to low
  }
  analogWrite(PWMB, abs(motorSpeed));  //now that the motor direction is set, drive it at the entered speed
}
