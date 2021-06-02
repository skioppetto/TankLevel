#include <hcsr04_range.h>
#include <Arduino.h>
HCSR04Range::HCSR04Range(int trig, int echo)
{
    this->trig = trig;
    this->echo = echo;
    this->interval = 0ul;
    this->ready = false;
    this->last_measure_ms = 0ul;
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

HCSR04Range::~HCSR04Range()
{
}

bool HCSR04Range::checkMinCycle(){
    return (last_measure_ms == 0 || millis() - last_measure_ms >= HCSR04_MIN_CYCLE_MS);
}

void HCSR04Range::trigger(){
    if (checkMinCycle()){
        //noInterrupts();     // disable interrupts to be more precise during pulse measure
        digitalWrite(trig, LOW);
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
        interval = pulseIn(echo, HIGH);
        //interrupts();       // reenable after returning a value
        last_measure_ms = millis();
        ready = true;
    }
}

bool HCSR04Range::isReady(){
    bool eval =  interval > 0ul && (checkMinCycle() || ready);
    ready = false;
    return eval;
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