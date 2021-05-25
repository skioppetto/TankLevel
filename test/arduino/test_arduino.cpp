#include<unity.h>
#include<Arduino.h>
#include "hcsr04_range/test_hcsr04_range.h"

void test_assert_running_arduino(){
    TEST_ASSERT_TRUE(true);
}

void setup(){
    
}

void loop()
{
    UNITY_BEGIN();
    RUN_TEST(test_assert_running_arduino);
    RUN_TEST(test_hcsr04_init);
    UNITY_END();
}
