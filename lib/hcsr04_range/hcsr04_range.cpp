#include <hcsr04_range.h>
#include <Arduino.h>
HCSR04Range::HCSR04Range(int trig, int echo)
{
    this->trig = trig;
    this->echo = echo;
    this->interval = 0ul;
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

HCSR04Range::~HCSR04Range()
{
}

void HCSR04Range::trigger(){
    //noInterrupts();     // disable interrupts to be more precise during pulse measure
    digitalWrite(trig, LOW);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    interval = pulseIn(echo, HIGH);
    //interrupts();       // reenable after returning a value
}

bool HCSR04Range::isReady(){
    return interval > 0ul;
}

unsigned long HCSR04Range::getIntervalMicros(){
    return interval;
}

unsigned int HCSR04Range::getDistanceCm(){
    return interval / 58ul;
}

unsigned int HCSR04Range::getDistanceInches(){
    return interval / 148ul;
}