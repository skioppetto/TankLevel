#include <unity.h>
#include <Arduino.h>
#include <hcsr04_range.h>
#include "test_hcsr04_range.h"




void test_hcsr04_init(){
    HCSR04Range r(HCSR04_TRIG_PIN, HCSR04_ECHO_PIN); 
    uint8_t trig_bit = digitalPinToBitMask(HCSR04_TRIG_PIN);
    uint8_t trig_port = digitalPinToPort(HCSR04_TRIG_PIN);
    uint8_t echo_bit = digitalPinToBitMask(HCSR04_ECHO_PIN);
    uint8_t echo_port = digitalPinToPort(HCSR04_ECHO_PIN);
    volatile uint8_t *trig_reg = portModeRegister(trig_port);
    volatile uint8_t *echo_reg = portModeRegister(echo_port);
    TEST_ASSERT_TRUE(*trig_reg & trig_bit);     // assert trigger has output pinMode
    TEST_ASSERT_FALSE(*echo_reg & echo_bit);    // assert echo has input pinMode
}

