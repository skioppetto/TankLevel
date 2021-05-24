#include <hcsr04_range.h>
#include <Arduino.h>
HCSR04Range::HCSR04Range(int trig, int echo)
{
    pinMode(trig, OUTPUT);
}

HCSR04Range::~HCSR04Range()
{
}
