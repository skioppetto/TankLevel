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
    HCSR04Range r(HCSR04_TRIG_PIN, HCSR04_ECHO_PIN);
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
    detachInterrupt(digitalPinToInterrupt(HCSR04_TRIG_PIN));
}

