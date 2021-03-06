#include <unity.h>
#include <hysteresis_level.h>

void test_hysteresis_level_eval(){
    HysteresisLevel hl(100, 5);
    TEST_ASSERT_EQUAL(HysteresisLevel::LEVEL_UNCHANGED,  hl.eval (103));
    TEST_ASSERT_EQUAL(HysteresisLevel::LEVEL_HIGH,  hl.eval (106));
    TEST_ASSERT_EQUAL(HysteresisLevel::LEVEL_LOW,  hl.eval (94));
}

// need an empty constructor and set values later to let allocate arrays. 
void test_hysteresis_setLevel(){
    HysteresisLevel hl;
    hl.setLevel(100, 5);
    TEST_ASSERT_EQUAL(HysteresisLevel::LEVEL_UNCHANGED,  hl.eval (103));
    TEST_ASSERT_EQUAL(HysteresisLevel::LEVEL_HIGH,  hl.eval (106));
   TEST_ASSERT_EQUAL(HysteresisLevel::LEVEL_LOW,  hl.eval (94));
}

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_hysteresis_level_eval);
    RUN_TEST(test_hysteresis_setLevel);
    UNITY_END();
    return 0;
}
