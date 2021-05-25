#include <unity.h>
#include <Arduino.h>
#include <hcsr04_range.h>
#include "test_hcsr04_range.h"




void test_hcsr04_init(){
    HCSR04Range r(HCSR04_TRIG_PIN, HCSR04_ECHO_PIN); 
}

// test trigger as output pin
void test_hcsr04_trig_output(){
    int state = digitalRead(HCSR04_TRIG_PIN);
    digitalWrite(HCSR04_TRIG_PIN, !state);
    TEST_ASSERT_EQUAL_INT(!state, digitalRead(HCSR04_TRIG_PIN));
    digitalWrite(HCSR04_TRIG_PIN, state);   // restore initial state
}