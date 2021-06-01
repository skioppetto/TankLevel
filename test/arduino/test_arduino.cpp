#include <unity.h>
#include <Arduino.h>
#include "hcsr04_range/test_hcsr04_range.h"

void test_assert_running_arduino()
{
    TEST_ASSERT_TRUE(true);
}

void setup()
{
    UNITY_BEGIN();
    delay(2000);
    RUN_TEST(test_assert_running_arduino);
    RUN_TEST(test_hcsr04_init);
    RUN_TEST(test_hcsr04_trigger);
    RUN_TEST(test_hcsr04_preconditions);
    RUN_TEST(test_hcsr04_isReady);
}

int count = 0;
void loop()
{
    while (count < 2)
    {
        Serial.println("set a distance...");
        delay(4000);
        RUN_TEST(test_hcsr04_interval1);
        Serial.println("move away the sensor...");
        delay(4000);
        RUN_TEST(test_hcsr04_interval2);
        count++;
    }
    UNITY_END();
}
