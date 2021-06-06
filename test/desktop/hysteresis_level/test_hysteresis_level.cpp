#include "test_hysteresis_level.h"
#include <unity.h>
#include <hysteresis_level.h>

void test_hysteresis_level_eval(){
    HysteresisLevel hl(100, 5);
    TEST_ASSERT_EQUAL(HysteresisLevel::UNCHANGED,  hl.eval (103));
    TEST_ASSERT_EQUAL(HysteresisLevel::HIGH,  hl.eval (106));
    TEST_ASSERT_EQUAL(HysteresisLevel::LOW,  hl.eval (94));
}