#include "MiniCar.h"
#include "src/timer/Timer.h"

MiniCar car;
Timer t;
int motorSpeed = 0;
int servoSpeed = 1300;

void setup()
{
  Serial.begin(9600);
  car.init();
  t.every(10, cbk);
  t.every(1000, measureDistance);
  t.every(5000, pseudoMessage);
}

void loop()
{
  // waitMessage()
  // routingMessage()
  t.update();
}
void cbk() // repeat every 10ms
{
  car.update();
}
void measureDistance()
{
  car.testUltra();
}
void pseudoMessage()
{
  motorSpeed = 255 - motorSpeed;
  car.rightSpeed(motorSpeed, 1);
  car.leftSpeed(motorSpeed, 1);

  servoSpeed = 3000 - servoSpeed;
  // car.headMove(servoSpeed, 1);
  car.headMove(servoSpeed, 2);
}