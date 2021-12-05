// see https://www.cnblogs.com/journeyonmyway/archive/2012/01/15/2323090.html
// see https://detail.tmall.com/item.htm?id=563699226824

#ifndef __ULTRASENSOR_H__
#define __ULTRASENSOR_H__

#include "Arduino.h"

class UltraSensor
{
  private:
    byte pin1,pin2,pinEn;
    
    
  public:
    UltraSensor(byte p1,byte p2,byte pe);
    ~UltraSensor();
    void setParams(int p, int d);
    int getParams();
    void on();
    void off();
    int pwm, dir;
  };
#endif
