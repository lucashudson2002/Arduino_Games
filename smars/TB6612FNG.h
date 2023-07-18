#pragma once

#include <Arduino.h>

class TB6612FNG{
private:
  int ain1;
  int ain2;
  int bin1;
  int bin2;
  int pwma;
  int pwmb;
  int stby;
public:
  TB6612FNG(int ain1, int ain2, int bin1, int bin2, int pwma, int pwmb, int stby);
  ~TB6612FNG();
  void begin();
  void forward(int pwma,int pwmb);
  void backward(int pwma,int pwmb);
  void right(int pwma,int pwmb);
  void left(int pwma,int pwmb);
  void brake();
  void stop();
};