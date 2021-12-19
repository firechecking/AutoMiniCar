// see https://www.cnblogs.com/journeyonmyway/archive/2012/01/15/2323090.html
// see https://detail.tmall.com/item.htm?id=563699226824

#ifndef __ULTRASENSOR_H__
#define __ULTRASENSOR_H__

#include "Arduino.h"

class UltraSensor
{
private:
  byte pinTrig, pinEcho;

public:
  UltraSensor();
  ~UltraSensor();
  void setPin(byte trig, byte echo);

  unsigned long measure();
};
#endif
