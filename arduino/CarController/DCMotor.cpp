#include "DCMotor.h"
#include "Arduino.h"

DCMotor::DCMotor() {}
DCMotor::~DCMotor() {}
void DCMotor::setPin(byte p1, byte p2, byte pe)
{
  pin1 = p1;
  pin2 = p2;
  pinEn = pe;
  pwm = 0;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pinEn, OUTPUT);
}
void DCMotor::setSpeed(int p, int d)
{
  pwm = p;
  dir = d;
  if (pwm == 0) // 停止电机
  {
    digitalWrite(pin1, 0);
    digitalWrite(pin2, 0);
    digitalWrite(pinEn, 0);
    return;
  }
  //开启电机
  if (dir == 0)
  {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  }
  else
  {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
  }
  analogWrite(pinEn, pwm);
}