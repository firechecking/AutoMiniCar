#ifndef __MINICAR_H__
#define __MINICAR_H__

#include <Arduino.h>
#include <Servo.h>
#include "DCMotor.h"
#include "UltraSensor.h"

#define MotorA_pin1 4
#define MotorA_pin2 5
#define MotorA_pinEn 6
#define MotorB_pin1 10
#define MotorB_pin2 9
#define MotorB_pinEn 11
#define Servo1_pin 7
#define Servo2_pin 8
#define Ultra_Trig 12
#define Ultra_Echo 13

#define MAX_MOTOR_SPEEDUP 1
#define MAX_SERVO_SPEEDUP 20

class MiniCar
{
private:
    DCMotor motor1, motor2;
    Servo servo1, servo2;
    UltraSensor ultraSensor;
    int leftSpeedCurrent, rightSpeedCurrent, leftSpeedTgt, rightSpeedTgt;
    int head1DegreeCurrent, head2DegreeCurrent, head1DegreeTgt, head2DegreeTgt;

public:
    MiniCar();
    ~MiniCar();
    void leftSpeed(int speed, int direction);
    void rightSpeed(int speed, int direction);
    void headMove(int degree, int index);
    void enableUltra();
    void startScan();
    void update();
    // test device
    void testMotor();
    void testServo();
    void testUltra();
};
#endif
