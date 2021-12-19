#include "UltraSensor.h"
UltraSensor::UltraSensor()
{
}
UltraSensor::~UltraSensor() {}
void UltraSensor::setPin(byte trig, byte echo)
{
    pinTrig = trig;
    pinEcho = echo;
    pinMode(pinTrig, OUTPUT);
    pinMode(pinEcho, INPUT);
}
unsigned long UltraSensor::measure()
{
    unsigned long time_echo_us = 0;
    unsigned long dist_mm = 0;

    // 通过Trig/Pin 发送脉冲，触发US-100 测距
    digitalWrite(pinTrig, LOW);  // 先拉低，以确保脉冲识别正确
    delayMicroseconds(2);        // 等待2us
    digitalWrite(pinTrig, HIGH); // 开始通过Trig/Pin 发送脉冲
    delayMicroseconds(12);       // 设置脉冲宽度为12us (>10us)
    digitalWrite(pinTrig, LOW);  // 结束脉冲

    time_echo_us = pulseIn(pinEcho, HIGH);            // 计算US-100 返回的脉冲宽度
    if ((time_echo_us < 60000) && (time_echo_us > 1)) // 脉冲有效范围(1, 60000).
    {
        // dist_mm = (time_echo_us * 0.34mm/us) / 2 (mm)
        dist_mm = time_echo_us * 5 / 29; // 通过脉冲宽度计算距离.
        return dist_mm; // 距离单位：毫米
    }
    return 0;
}