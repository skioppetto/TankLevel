#include <hcsr04_range.h>
#include <Arduino.h>
HCSR04Range::HCSR04Range(int trig, int echo)
{
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT); // this declaration won't be tested
}

HCSR04Range::~HCSR04Range()
{
}
