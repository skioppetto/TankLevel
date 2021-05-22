#include<unity.h>
#include<Arduino.h>

void test_assert_running_arduino(){
    TEST_ASSERT_TRUE(true);
}

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_assert_running_arduino);
    UNITY_END();
    return 0;
}
