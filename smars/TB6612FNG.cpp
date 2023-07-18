#include "TB6612FNG.h"

TB6612FNG::TB6612FNG(int ain1, int ain2, int bin1, int bin2, int pwma, int pwmb, int stby){
  this->ain1 = ain1;
  this->ain2 = ain2;
  this->bin1 = bin1;
  this->bin2 = bin2;
  this->pwma = pwma;
  this->pwmb = pwmb;
  this->stby = stby;
}

TB6612FNG::~TB6612FNG(){}

void TB6612FNG::begin(){
  pinMode(this->ain1, OUTPUT);
  pinMode(this->ain2, OUTPUT);
  pinMode(this->bin1, OUTPUT);
  pinMode(this->bin2, OUTPUT);
  pinMode(this->pwma, OUTPUT);
  pinMode(this->pwmb, OUTPUT);
  pinMode(this->stby, OUTPUT);
  stop();
}

void TB6612FNG::forward(int pwma,int pwmb){
  digitalWrite(this->ain1, HIGH);
  digitalWrite(this->ain2, LOW);
  digitalWrite(this->bin1, HIGH);
  digitalWrite(this->bin2, LOW);
  analogWrite(this->pwma, pwma);
  analogWrite(this->pwmb, pwmb);
  digitalWrite(this->stby, HIGH);
}
void TB6612FNG::backward(int pwma,int pwmb){
  digitalWrite(this->ain1, LOW);
  digitalWrite(this->ain2, HIGH);
  digitalWrite(this->bin1, LOW);
  digitalWrite(this->bin2, HIGH);
  analogWrite(this->pwma, pwma);
  analogWrite(this->pwmb, pwmb);
  digitalWrite(this->stby, HIGH);
}
void TB6612FNG::right(int pwma,int pwmb){
  digitalWrite(this->ain1, HIGH);
  digitalWrite(this->ain2, LOW);
  digitalWrite(this->bin1, LOW);
  digitalWrite(this->bin2, HIGH);
  analogWrite(this->pwma, pwma);
  analogWrite(this->pwmb, pwmb);
  digitalWrite(this->stby, HIGH);
}
void TB6612FNG::left(int pwma,int pwmb){
  digitalWrite(this->ain1, LOW);
  digitalWrite(this->ain2, HIGH);
  digitalWrite(this->bin1, HIGH);
  digitalWrite(this->bin2, LOW);
  analogWrite(this->pwma, pwma);
  analogWrite(this->pwmb, pwmb);
  digitalWrite(this->stby, HIGH);
}
void TB6612FNG::brake(){
  digitalWrite(this->ain1, HIGH);
  digitalWrite(this->ain2, HIGH);
  digitalWrite(this->bin1, HIGH);
  digitalWrite(this->bin2, HIGH);
  analogWrite(this->pwma, 255);
  analogWrite(this->pwmb, 255);
  digitalWrite(this->stby, HIGH);
}
void TB6612FNG::stop(){
  digitalWrite(this->ain1, LOW);
  digitalWrite(this->ain2, LOW);
  digitalWrite(this->bin1, LOW);
  digitalWrite(this->bin2, LOW);
  analogWrite(this->pwma, 0);
  analogWrite(this->pwmb, 0);
  digitalWrite(this->stby, LOW);
}