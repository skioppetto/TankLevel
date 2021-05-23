#include<unity.h>
#include "tank_level\test_tank_level.h"

void test_assert_running_desktop(){
    TEST_ASSERT_TRUE(true);
}

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_assert_running_desktop);
    RUN_TEST(test_tank_level_init);
    RUN_TEST(test_set_measure);
    UNITY_END();
    return 0;
}
