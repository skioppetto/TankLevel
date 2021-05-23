#include<unity.h>
#include<tank_level.h>

void test_tank_level_calculate_defaults(){
    TankLevel tl;
} 

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_tank_level_calculate_defaults);
    UNITY_END();
    return 0;
}
