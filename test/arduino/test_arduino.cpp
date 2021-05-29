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
    UNITY_END();
}

void loop()
{
    
}
