#include "MiniCar.h"

MiniCar::MiniCar()
{
}
MiniCar::~MiniCar() {}
void MiniCar::init()
{
    motor1.setPin(MotorA_pin1, MotorA_pin2, MotorA_pinEn);
    motor2.setPin(MotorB_pin1, MotorB_pin2, MotorB_pinEn);
    servo1.attach(Servo1_pin);
    servo2.attach(Servo2_pin);

    leftSpeedCurrent = 0;
    rightSpeedCurrent = 0;
    leftSpeedTgt = 0;
    rightSpeedTgt = 0;

    head1DegreeCurrent = 1400;
    head2DegreeCurrent = 1400;
    head1DegreeTgt = 1500;
    head2DegreeTgt = 1500;
}
int getSpeedUpValue(int crt, int tgt, int max_speedup)
{
    if (tgt > crt)
    {
        crt += min(max_speedup, tgt - crt);
    }
    else
    {
        crt -= min(max_speedup, crt - tgt);
    }
    return crt;
}
void MiniCar::update()
{
    // 每隔10ms调用一次，限定点击加速度
    if (leftSpeedCurrent != leftSpeedTgt)
    {
        leftSpeedCurrent = getSpeedUpValue(leftSpeedCurrent, leftSpeedTgt, MAX_MOTOR_SPEEDUP);
        motor1.setSpeed(abs(leftSpeedCurrent), int(leftSpeedCurrent > 0));
    }
    if (rightSpeedCurrent != rightSpeedTgt)
    {
        rightSpeedCurrent = getSpeedUpValue(rightSpeedCurrent, rightSpeedTgt, MAX_MOTOR_SPEEDUP);
        motor2.setSpeed(abs(rightSpeedCurrent), int(rightSpeedCurrent > 0));
    }

    if (head1DegreeCurrent != head1DegreeTgt)
    {
        head1DegreeCurrent = getSpeedUpValue(head1DegreeCurrent, head1DegreeTgt, MAX_SERVO_SPEEDUP);
        servo1.writeMicroseconds(head1DegreeCurrent + SERVO1_OFFSET);
    }
    if (head2DegreeCurrent != head2DegreeTgt)
    {
        head2DegreeCurrent = getSpeedUpValue(head2DegreeCurrent, head2DegreeTgt, MAX_SERVO_SPEEDUP);
        servo2.writeMicroseconds(head2DegreeCurrent + SERVO2_OFFSET);
    }
}

void MiniCar::leftSpeed(int speed, int direction)
{
    if (direction > 0)
        leftSpeedTgt = speed;
    else
        leftSpeedTgt = -speed;
}
void MiniCar::rightSpeed(int speed, int direction)
{
    if (direction > 0)
        rightSpeedTgt = speed;
    else
        rightSpeedTgt = -speed;
}
void MiniCar::headMove(int degree, int index)
{
    if (index == 1)
    {
        head1DegreeTgt = degree;
    }
    else
    {
        head2DegreeTgt = degree;
    }
}
void MiniCar::testMotor()
{
    motor1.setSpeed(200, 1);
    motor2.setSpeed(200, 1);
    delay(1500);
    motor1.setSpeed(0, 1);
    motor2.setSpeed(0, 1);
    delay(1000);

    motor1.setSpeed(200, 0);
    motor2.setSpeed(200, 0);
    delay(1500);
    motor1.setSpeed(0, 1);
    motor2.setSpeed(0, 1);
    delay(1000);
}
void MiniCar::testServo()
{
    int start = 1200;
    int end = 1800;
    servo1.write(90);
    servo2.write(90);
    delay(10);
    // for (int pos = 1500; pos <= end; pos++)
    // {
    //     servo1.writeMicroseconds(pos);
    //     delay(5);
    // }
    // for (int pos = end; pos >= start; pos--)
    // {
    //     servo1.writeMicroseconds(pos);
    //     delay(5);
    // }
    // for (int pos = start; pos <= 1500; pos++)
    // {
    //     servo1.writeMicroseconds(pos);
    //     delay(5);
    // }
}
void MiniCar::testUltra()
{
    unsigned long dist_mm = ultraSensor.measure();
    if (dist_mm > 0)
    {
        Serial.print("Distance is: "); // 输出结果至串口监视器
        Serial.print(dist_mm, DEC);    // 输出结果至串口监视器
        Serial.println("mm");          // 输出结果至串口监视器
    }
}
