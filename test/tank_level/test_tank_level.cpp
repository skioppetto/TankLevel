#include<unity.h>
#include<tank_level.h>

// tank_level need to be initiated passing at least the height, the min_height and number of levels. 
void init_tank_level(TankLevel *tl, int minHeight){
    tl->setMinHeight(minHeight);
}

void test_tank_level_init(){
    TankLevel tl(100, 4);
    init_tank_level(&tl, 10);
    TEST_ASSERT_EQUAL_INT(100, tl.getHeight());
    TEST_ASSERT_EQUAL_INT(10, tl.getMinHeight());
    TEST_ASSERT_EQUAL_INT(4, tl.getLevels());
} 


// measure set
void test_set_measure(){
    TankLevel tl(100, 4); 
    tl.setMeasure (50);
    TEST_ASSERT_EQUAL_INT(50, tl.getMeasure());
}

void test_calculate_level(TankLevel &tl, int measure, int level){
    tl.setMeasure(measure);
    TEST_ASSERT_EQUAL_INT(level, tl.getLevel());
}

void test_calculate_levels_4(){
    TankLevel tl(100, 4);
    init_tank_level(&tl, 10);
   test_calculate_level(tl, 102, TankLevel::LEVEL_OVERFLOW); 
    test_calculate_level(tl, 91, TankLevel::LEVEL_LOW);
    test_calculate_level(tl, 78, 1);
    test_calculate_level(tl, 60, 2);
    test_calculate_level(tl, 45, 3);
    test_calculate_level(tl, 20, 4);
}

void test_calculate_levels_5(){
    TankLevel tl(100, 5);
    init_tank_level(&tl, 10);
    test_calculate_level(tl, 91, TankLevel::LEVEL_LOW);
    test_calculate_level(tl, 85, 1);
    test_calculate_level(tl, 66, 2);
    test_calculate_level(tl, 48, 3);
    test_calculate_level(tl, 24, 4);
    test_calculate_level(tl, 10, 5);
}

void test_calculate_levels_8_height_80(){
    TankLevel tl(80, 8);
    init_tank_level(&tl, 5);
    test_calculate_level(tl, 97, TankLevel::LEVEL_OVERFLOW);
    test_calculate_level(tl, 79, TankLevel::LEVEL_LOW);
    test_calculate_level(tl, 75, 1);
    test_calculate_level(tl, 66, 2);
    test_calculate_level(tl, 55, 3);
    test_calculate_level(tl, 44, 4);
    test_calculate_level(tl, 38, 5);
    test_calculate_level(tl, 27, 6);
    test_calculate_level(tl, 13, 7);
    test_calculate_level(tl, 6, 8);
}

void test_update_levels_runtime(){
    TankLevel tl(80, 8);
    init_tank_level(&tl, 5);
    //tl.setHysteresis(2);
    test_calculate_level(tl, 44, 4);
    test_calculate_level(tl, 27, 6);
    tl.setLevels(2);
    test_calculate_level(tl, 44, 1);
    test_calculate_level(tl, 27, 2);
    
}

void test_hysteresis_level_up(){
    TankLevel tl(80, 8);
    init_tank_level(&tl, 5);
    // step between levels is 10, set an hysteresis of 2
    tl.setHysteresis(2);
    // first level is freely set, level 4 is from 50 to 40
    test_calculate_level(tl, 44, 4);
    // to go up to level 5, need to be < 38
    test_calculate_level(tl, 38, 4);
    test_calculate_level(tl, 37, 5);
    // to go back to level 4, need to be > 42
    //test_calculate_level(tl, 42, 5);
    //test_calculate_level(tl, 45, 4);
}

void test_hysteresis_level_down(){
    TankLevel tl(80, 8);
    init_tank_level(&tl, 5);
    // step between levels is 10, set an hysteresis of 2
    tl.setHysteresis(2);
    // first level is freely set, level 4 is from 50 to 40
    test_calculate_level(tl, 44, 4);
    // to go down to level 3, need to be > 52
    test_calculate_level(tl, 52, 4);
    test_calculate_level(tl, 53, 3);
    // to go back to level 4, need to be > 42
    //test_calculate_level(tl, 42, 5);
    //test_calculate_level(tl, 45, 4); 
}

void test_tank_level_init_level_0(){
    TankLevel tl(80, 0);
    TEST_ASSERT_EQUAL(1, tl.getLevels()); // test levels has min value 1 
}

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_tank_level_init);
    RUN_TEST(test_tank_level_init_level_0);
    RUN_TEST(test_set_measure);
    RUN_TEST(test_calculate_levels_4);
    RUN_TEST(test_calculate_levels_5);
    RUN_TEST(test_calculate_levels_8_height_80);
    RUN_TEST(test_update_levels_runtime);
    RUN_TEST(test_hysteresis_level_up);
    RUN_TEST(test_hysteresis_level_down);
    UNITY_END();
    return 0;
}