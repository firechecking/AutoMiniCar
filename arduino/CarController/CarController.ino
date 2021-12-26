#include "MiniCar.h"
#include "src/timer/Timer.h"

MiniCar car;
Timer t;
int motorSpeed = 0;
int servoSpeed = 1300;
int command;

void setup()
{
  Serial.begin(9600);
  car.init();
  t.every(10, cbk);
  t.every(50, measureDistance);
//  t.every(5000, pseudoMessage);
  car.headMove(1500, 2);
}

void loop()
{
  // waitMessage()
  // routingMessage()
  t.update();
  if (Serial.available()){
    char command = (char)Serial.read();
    if (command == 'a') {
        int angleBias = (int)Serial.read();
        car.headMove(((angleBias - 128) / 127.0 * 750) + 1500, 2);
        Serial.print("angleBias=");
        Serial.println(angleBias);
    }
    else if (command == 'm') {
      car.headMove(1500, 2);
    }
  }
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
//  motorSpeed = 255 - motorSpeed;
//  car.rightSpeed(motorSpeed, 1);
//  car.leftSpeed(motorSpeed, 1);

  servoSpeed = 3000 - servoSpeed;
  // car.headMove(servoSpeed, 1);
  car.headMove(servoSpeed, 2);
}
