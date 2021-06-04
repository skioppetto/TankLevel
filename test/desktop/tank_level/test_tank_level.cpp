#include<unity.h>
#include<tank_level.h>

// tank_level need to be initiated passing at least the height, the min_height and number of levels. 
void init_tank_level(TankLevel &tl, int height, int minHeight, int levels){
    tl.setHeight(height);
    tl.setMinHeight(minHeight);
    tl.setLevels(levels);
}

void test_tank_level_init(){
    TankLevel tl;
    init_tank_level(tl, 100, 10, 4);
    TEST_ASSERT_EQUAL_INT(100, tl.getHeight());
    TEST_ASSERT_EQUAL_INT(10, tl.getMinHeight());
    TEST_ASSERT_EQUAL_INT(4, tl.getLevels());
} 


// measure set
void test_set_measure(){
    TankLevel tl; 
    tl.setMeasure (50);
    TEST_ASSERT_EQUAL_INT(50, tl.getMeasure());
}

void test_calculate_level(TankLevel &tl, int measure, int level){
    tl.setMeasure(measure);
    TEST_ASSERT_EQUAL_INT(level, tl.getLevel());
}

void test_calculate_levels_4(){
    TankLevel tl;
    init_tank_level(tl, 100, 10, 4);
    test_calculate_level(tl, 102, TankLevel::LEVEL_OVERFLOW); 
    test_calculate_level(tl, 91, TankLevel::LEVEL_LOW);
    test_calculate_level(tl, 78, 1);
    test_calculate_level(tl, 60, 2);
    test_calculate_level(tl, 45, 3);
    test_calculate_level(tl, 20, 4);
}

void test_calculate_levels_5(){
    TankLevel tl;
    init_tank_level(tl, 100, 10, 5);
    test_calculate_level(tl, 91, TankLevel::LEVEL_LOW);
    test_calculate_level(tl, 85, 1);
    test_calculate_level(tl, 66, 2);
    test_calculate_level(tl, 48, 3);
    test_calculate_level(tl, 24, 4);
    test_calculate_level(tl, 10, 5);
}

void test_calculate_levels_8_height_80(){
    TankLevel tl;
    init_tank_level(tl, 80, 5, 8);
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
    TankLevel tl;
    init_tank_level(tl, 80, 5, 8);
    test_calculate_level(tl, 44, 4);
    test_calculate_level(tl, 27, 6);
    tl.setLevels(2);
    test_calculate_level(tl, 44, 1);
    test_calculate_level(tl, 27, 2);
    
}