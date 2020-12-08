#define MAX_SPEED 255  // максимальный сигнал на мотор (max 255)
#define IN1 2
#define IN2 3
#define IN3 10
#define IN4 11
#define ECHO_PIN 6
#define TRIG_PIN 7
#define SENSOR_PIN 4
#define MAX_DISTANCE 200

#include <Servo.h>
#include "GyverMotor.h"
#include <NewPing.h>
GMotor motorL(IN1, IN2);
GMotor motorR(IN3, IN4);
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
boolean goesForward = false;
int distance = 100;
int speedSet = 0;
int sensorState = 0;
Servo myservo;


void setup() {
  Serial.begin(9600);
  motorR.setMode(STOP);
  motorL.setMode(STOP);
  pinMode(SENSOR_PIN, INPUT);
  myservo.attach(5);
  lookForward();
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  int distanceR = 0;
  int distanceL =  0;
  delay(40);


  Serial.print(distance);
  Serial.print(" cm");
  Serial.println();


  Serial.print(sensorState);
  Serial.print(" sn");
  Serial.println();

  if (sensorState == HIGH) {
    if (distance <= 25) {
      moveStop();
      delay(100);
      moveBackward();
      delay(300);
      moveStop();
      delay(200);
      distanceR = lookRight();
      delay(200);
      lookForward();
      delay(200);
      distanceL = lookLeft();
      delay(200);
      lookForward();
      delay(200);

      if (distanceR >= distanceL) {
        delay(100);
        turnRight();
        delay(300);
        moveStop();
        delay(200);
        Serial.println("turnRight");
      } else {
        delay(100);
        turnLeft();
        delay(300);
        moveStop();
        delay(200);
        Serial.println("turnLeft");
      }
    } else {
      moveForward();
    }
    distance = readPing();
  } else {
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    lookForward();
    delay(200);
    distanceL = lookLeft();
    delay(200);
    lookForward();
    delay(200);
  }
  sensorState = digitalRead(SENSOR_PIN);
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0)
  {
    cm = 250;
  }
  return cm;
}

int lookForward()
{
  myservo.write(90);
  delay(200);
}

int lookRight()
{
  myservo.write(10);
  delay(500);
  int distance = readPing();
  delay(100);
  return distance;
}

int lookLeft()
{
  myservo.write(180);
  delay(500);
  int distance = readPing();
  delay(100);
  return distance;
}


void moveStop() {
  motorR.setMode(STOP);
  motorL.setMode(STOP);
}

void moveForward() {
  if (!goesForward) {
    goesForward = true;
    motorR.setMode(FORWARD);
    motorL.setMode(FORWARD);
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
      motorR.setSpeed(speedSet);
      motorL.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveBackward() {
  goesForward = false;
  motorR.setMode(BACKWARD);
  motorL.setMode(BACKWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
    motorR.setSpeed(speedSet);
    motorL.setSpeed(speedSet);
    delay(5);
  }
}

void turnRight() {
  motorL.setMode(BACKWARD);
  motorR.setMode(FORWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
    motorR.setSpeed(speedSet);
    motorL.setSpeed(speedSet);
    delay(5);
  }
}

void turnLeft() {
  motorR.setMode(BACKWARD);
  motorL.setMode(FORWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
    motorR.setSpeed(speedSet);
    motorL.setSpeed(speedSet);
    delay(5);
  }
}
