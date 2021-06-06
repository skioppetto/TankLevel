#include <unity.h>
#include <Arduino.h>
#include <hcsr04_range.h>
#include "test_hcsr04_range.h"

void test_hcsr04_init()
{
    HCSR04Range r(HCSR04_TRIG_PIN, HCSR04_ECHO_PIN);
    uint8_t trig_bit = digitalPinToBitMask(HCSR04_TRIG_PIN);
    uint8_t trig_port = digitalPinToPort(HCSR04_TRIG_PIN);
    uint8_t echo_bit = digitalPinToBitMask(HCSR04_ECHO_PIN);
    uint8_t echo_port = digitalPinToPort(HCSR04_ECHO_PIN);
    volatile uint8_t *trig_reg = portModeRegister(trig_port);
    volatile uint8_t *echo_reg = portModeRegister(echo_port);
    TEST_ASSERT_TRUE(*trig_reg & trig_bit);  // assert trigger has output pinMode
    TEST_ASSERT_FALSE(*echo_reg & echo_bit); // assert echo has input pinMode
}

unsigned long pulse_start;
volatile unsigned long pulse_duration;
int pulse_pin;

void evaluate_pulse_duration()
{
    int state = digitalRead(pulse_pin);
    if (state)
    {
        pulse_start = micros();
    }
    else
    {
        pulse_duration = micros() - pulse_start;
    }
}

void test_hcsr04_trigger()
{
    // to test it I'll attach an interrupt to the trigger pin,
    // it means that for arduino uno will be only pin 2 or 3
 /*   HCSR04Range r(HCSR04_TRIG_PIN, HCSR04_ECHO_PIN);
    TEST_ASSERT_TRUE_MESSAGE(HCSR04_TRIG_PIN == 2 || HCSR04_TRIG_PIN == 3, "trigger must be bind to pin 2 or 3 because an interrupt is needed");
    attachInterrupt(digitalPinToInterrupt(HCSR04_TRIG_PIN), evaluate_pulse_duration, CHANGE);
    pulse_pin = HCSR04_TRIG_PIN; 
    pulse_duration = 0;
    r.trigger(); 
    String message = "trigger duration: ";
    message.concat(pulse_duration);
    message.concat(" us");
    Serial.println(message);        // print out the pulse duration 
    TEST_ASSERT_TRUE_MESSAGE(pulse_duration >= 10, message.c_str());
    detachInterrupt(digitalPinToInterrupt(HCSR04_TRIG_PIN)); */
}

void test_hcsr04_preconditions(){
    HCSR04Range r(HCSR04_TRIG_PIN, HCSR04_ECHO_PIN);
    TEST_ASSERT_FALSE(r.isReady());
    TEST_ASSERT_EQUAL(0, r.getIntervalMicros());
}

void hcsr04_isReady(HCSR04Range r){
    long test_start = millis();
    r.trigger();
    TEST_ASSERT_TRUE(r.isReady());
}

// this test need to connect the sensor 
void test_hcsr04_isReady(){
    HCSR04Range r(HCSR04_TRIG_PIN, HCSR04_ECHO_PIN);
    hcsr04_isReady(r);
    unsigned long interval = r.getIntervalMicros();
    String message = "isReady: ";
    message.concat(r.isReady());
    Serial.println(message);
}

unsigned long  hcsr04_interval(HCSR04Range r){
    hcsr04_isReady(r);
    unsigned long interval = r.getIntervalMicros();
    String message = "interval duration: ";
    message.concat(interval);
    message.concat(" us");
    Serial.println(message);        // print out the pulse duration
    return interval;
}

unsigned long interval1;
void test_hcsr04_interval1(){
    HCSR04Range r(HCSR04_TRIG_PIN, HCSR04_ECHO_PIN);
    interval1 = hcsr04_interval(r);
    TEST_ASSERT_TRUE(interval1 > 0);  
}

void test_hcsr04_interval2(){
    HCSR04Range r(HCSR04_TRIG_PIN, HCSR04_ECHO_PIN);
    unsigned long interval2 = hcsr04_interval(r);
    TEST_ASSERT_TRUE_MESSAGE(interval1 < interval2, "second measure should be farther");  
}