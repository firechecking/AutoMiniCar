#include "DCMotor.h"
#include <Servo.h>

#define MotorA_pin1 4
#define MotorA_pin2 5
#define MotorA_pinEn 6
#define MotorB_pin1 10
#define MotorB_pin2 9
#define MotorB_pinEn 11
#define Servo1_pin 7
#define Servo2_pin 8
#define Ultra_Trig 12
#define Ultri_Echo 13

DCMotor motor1(MotorA_pin1, MotorA_pin2, MotorA_pinEn);
DCMotor motor2(MotorB_pin1, MotorB_pin2, MotorB_pinEn);
Servo servo1, servo2;

void setup()
{
  init_uart();
  init_attach();
}

void loop()
{
  Serial.print(motor1.getParams());
  Serial.print(motor2.getParams());

  // test_motor();

  test_servo(servo1);
  test_servo(servo2);
  // test_ultra();
}
void init_uart()
{
  Serial.begin(9600);
  Serial.print("Start");
}
void init_attach()
{
  servo1.attach(Servo1_pin);
  servo2.attach(Servo2_pin);

  pinMode(Ultra_Trig, OUTPUT); 
  pinMode(Ultri_Echo, INPUT); 
}
void test_motor()
{
  motor1.setParams(200, 1);
  motor2.setParams(200, 1);
  motor1.on();
  motor2.on();
  delay(1500);
  motor1.off();
  motor2.off();
  delay(1000);

  motor1.setParams(200, 0);
  motor2.setParams(200, 0);
  motor1.on();
  motor2.on();
  delay(1500);
  motor1.off();
  motor2.off();
  delay(1000);
}
void test_servo(Servo servo)
{
  // for (int pos = 0; pos <= 180; pos++)
  // {
  //   servo.write(pos);
  //   delay(5);
  // }
  // for (int pos = 180; pos >= 0; pos--)
  // {
  //   servo.write(pos);
  //   delay(5);
  // }
  servo.write(90);
}
void test_ultra()
{
  unsigned long time_echo_us = 0;
  unsigned long dist_mm = 0;
  
  // 通过Trig/Pin 发送脉冲，触发US-100 测距
  digitalWrite(Ultra_Trig, LOW);   // 先拉低，以确保脉冲识别正确
  delayMicroseconds(2);         // 等待2us
  digitalWrite(Ultra_Trig, HIGH);  // 开始通过Trig/Pin 发送脉冲
  delayMicroseconds(12);        // 设置脉冲宽度为12us (>10us)
  digitalWrite(Ultra_Trig, LOW);   // 结束脉冲
  
  time_echo_us = pulseIn(Ultri_Echo, HIGH);          // 计算US-100 返回的脉冲宽度
  if((time_echo_us < 60000) && (time_echo_us > 1))// 脉冲有效范围(1, 60000).
  {
    // dist_mm = (time_echo_us * 0.34mm/us) / 2 (mm)
    dist_mm = time_echo_us*5/29;        // 通过脉冲宽度计算距离.
    
    Serial.print("Distance is: ");      // 输出结果至串口监视器
    Serial.print(dist_mm, DEC);         // 输出结果至串口监视器
    Serial.println("mm");               // 输出结果至串口监视器
  }
  
  delay(500); // 每秒测量2次
}