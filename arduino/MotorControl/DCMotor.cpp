#include "DCMotor.h"
#include "Arduino.h"

DCMotor::DCMotor(byte p1,byte p2,byte pe){
  pin1 = p1;
  pin2 = p2;
  pinEn = pe;
  pwm = 0;
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pinEn,OUTPUT);
}

DCMotor::~DCMotor(){}

void DCMotor::setParams(int p, int d){
  pwm = p;
  dir = d;
}

int DCMotor::getParams(){
  return pwm;  
}

void DCMotor::on(){
  if (dir==0){
    digitalWrite(pin1,HIGH);
    digitalWrite(pin2,LOW);
  }
  else{
    digitalWrite(pin1,LOW);
    digitalWrite(pin2,HIGH);
  }
  analogWrite(pinEn,pwm);
}

void DCMotor::off(){
  digitalWrite(pin1,0);
  digitalWrite(pin2,0);  
  analogWrite(pinEn,0);
}
