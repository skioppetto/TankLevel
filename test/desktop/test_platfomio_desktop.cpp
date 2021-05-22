#include<unity.h>

void test_assert_running(){
    TEST_ASSERT_TRUE(true);
}

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_assert_running);
    UNITY_END();
    return 0;
}
