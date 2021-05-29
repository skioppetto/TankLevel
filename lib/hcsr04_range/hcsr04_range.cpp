#include <hcsr04_range.h>
#include <Arduino.h>
HCSR04Range::HCSR04Range(int trig, int echo)
{
    this->trig = trig;
    this->echo = echo;
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

HCSR04Range::~HCSR04Range()
{
}

void HCSR04Range::trigger(){
    digitalWrite(this->trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->trig, LOW);
    noInterrupts();     // disable interrupts to be more precise during pulse measure
    this->interval = pulseIn(echo, HIGH);
    interrupts();       // reenable after returning a value
}

bool HCSR04Range::isReady(){
    return true;
}

unsigned long HCSR04Range::getIntervalMicros(){
    return interval;
}