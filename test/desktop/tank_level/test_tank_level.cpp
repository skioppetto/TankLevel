#include<unity.h>
#include<tank_level.h>

// tank_level need to be initiated passing at least the height, the min_height and number of levels. 
void init_tank_level(TankLevel &tl, int height, int minHeight, int levels){
    tl.setHeightCm(height);
    tl.setMinHeightCm(minHeight);
    tl.setLevels(levels);
}

void test_tank_level_init(){
    TankLevel tl;
    init_tank_level(tl, 100, 10, 4);
    TEST_ASSERT_EQUAL_INT(100, tl.getHeightCm());
    TEST_ASSERT_EQUAL_INT(10, tl.getMinHeightCm());
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
    test_calculate_level(tl, 91, 0);
    test_calculate_level(tl, 78, 1);
    test_calculate_level(tl, 60, 2);
    test_calculate_level(tl, 45, 3);
    test_calculate_level(tl, 20, 4);
}