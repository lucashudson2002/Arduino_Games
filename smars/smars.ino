#include <Servo.h>
#include <HCSR04.h>
#include "TB6612FNG.h"
#include <ArduinoJson.h>
#include "music.h"

#define TRIG_BACK 2
#define BUZZER 3
#define ECHO_BACK 4
#define PWMA 5
#define AIN2 6
#define AIN1 7
#define STBY 8
#define BIN1 9
#define BIN2 10
#define PWMB 11
#define LED 13
#define SERVO A0
#define ECHO_FRONT A1
#define TRIG_FRONT A2
#define VREF A4
#define CLK A5
#define CS A6
#define DIN A7

#define DIST_MIN 20
#define SERVO_90 500
#define MEIA_VOLTA 500

int vel_left = 0;
int vel_right = 0;
String direction = "S";
String mode = "A";
bool horn = false;

UltraSonicDistanceSensor front_eyes(TRIG_FRONT, ECHO_FRONT);
UltraSonicDistanceSensor back_eyes(TRIG_BACK, ECHO_BACK);
Servo eyes;
TB6612FNG robot(BIN2, BIN1, AIN1, AIN2, PWMB, PWMA, STBY);
DynamicJsonDocument jsonReceive(256);
DynamicJsonDocument jsonSend(256);

void sendBluetooth();
void receiveBluetooth();
void autonomous();
void bluetooth();
void off();
void obstacle();

void setup(){
  Serial.begin(9600);
  eyes.attach(SERVO);
  eyes.write(90);
  robot.begin();
  pinMode(BUZZER, OUTPUT);
  pinMode(VREF, INPUT);
  pinMode(LED, OUTPUT);
  jsonReceive.clear();
  jsonReceive["left"] = 0;
  jsonReceive["right"] = 0;
  jsonReceive["direction"] = "S";
  jsonReceive["mode"] = "A";
  jsonReceive["horn"] = false;
}

void loop(){
  robot.forward(100, 100);
  delay(1000);
  robot.backward(100, 100);
  delay(1000);
  robot.right(100, 100);
  delay(1000);
  robot.left(100, 100);
  delay(1000);
}
