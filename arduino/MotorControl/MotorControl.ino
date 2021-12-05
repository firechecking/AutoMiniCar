#include "DCMotor.h"

#define MotorA_pin1 4
#define MotorA_pin2 5
#define MotorA_pinEn 6
#define MotorB_pin1 10
#define MotorB_pin2 9
#define MotorB_pinEn 11

DCMotor motor1(MotorA_pin1,MotorA_pin2,MotorA_pinEn);
DCMotor motor2(MotorB_pin1,MotorB_pin2,MotorB_pinEn);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  Serial.print(motor1.getParams());
  Serial.print(motor2.getParams());
  
  motor1.setParams(200,1);
  motor2.setParams(200,1);
  motor1.on();
  motor2.on();
  delay(1500);
  motor1.off();
  motor2.off();
  delay(1000);
  
  motor1.setParams(200,0);
  motor2.setParams(200,0);
  motor1.on();
  motor2.on();
  delay(1500);
  motor1.off();
  motor2.off();
  delay(1000);
}
