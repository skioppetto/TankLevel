#include <unity.h>
#include <Arduino.h>
#include <hcsr04_range.h>
#include "test_hcsr04_range.h"


void test_hcsr04_init(){
    HCSR04Range r(HCSR04_TRIG_PIN, HCSR04_ECHO_PIN); 
}