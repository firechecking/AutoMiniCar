#ifndef __DCMOTOR_H__
#define __DCMOTOR_H__

#include "Arduino.h"

class DCMotor
{
private:
  byte pin1, pin2, pinEn;
  int pwm, dir;

public:
  DCMotor();
  ~DCMotor();
  void setPin(byte p1, byte p2, byte pe);
  void setSpeed(int p, int d);
};
#endif
