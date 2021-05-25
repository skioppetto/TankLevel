#include <hcsr04_range.h>
#include <Arduino.h>
HCSR04Range::HCSR04Range(int trig, int echo)
{
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

HCSR04Range::~HCSR04Range()
{
}

void HCSR04Range::trigger(){}
