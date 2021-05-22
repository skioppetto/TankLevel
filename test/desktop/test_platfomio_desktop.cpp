#include<unity.h>

void test_assert_running_desktop(){
    TEST_ASSERT_TRUE(true);
}

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_assert_running_desktop);
    UNITY_END();
    return 0;
}
