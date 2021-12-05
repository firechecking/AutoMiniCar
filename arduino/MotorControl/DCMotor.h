#ifndef __DCMOTOR_H__
#define __DCMOTOR_H__

#include "Arduino.h"

class DCMotor
{
  private:
    byte pin1,pin2,pinEn;
    
    
  public:
    DCMotor(byte p1,byte p2,byte pe);
    ~DCMotor();
    void setParams(int p, int d);
    int getParams();
    void on();
    void off();
    int pwm, dir;
  };
#endif
