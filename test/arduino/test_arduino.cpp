#include<unity.h>
#include<Arduino.h>
#include "hcsr04_range/test_hcsr04_range.h"

void test_assert_running_arduino(){
    TEST_ASSERT_TRUE(true);
}

void setup(){
    UNITY_BEGIN();
    delay(2000);
    RUN_TEST(test_assert_running_arduino);
    RUN_TEST(test_hcsr04_init);
    RUN_TEST(test_hcsr04_trigger);
    RUN_TEST(test_hcsr04_isReady);
    Serial.println("set a distance...");
    delay(5000);
    RUN_TEST(test_hcsr04_interval1); 
    Serial.println("change the distance...");
    delay(5000);
    RUN_TEST(test_hcsr04_interval2); 
    UNITY_END();
}

void loop()
{
    
}
