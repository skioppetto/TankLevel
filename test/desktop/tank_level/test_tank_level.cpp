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
