#include<unity.h>
#include<tank_level.h>

// tank_level need to be initiated passing at least the height, the min_height and number of levels. 
void test_tank_level_init(){
    TankLevel tl;
    tl.setHeightCm(100);
    tl.setMinHeightCm(10);
    tl.setLevels(4);
    TEST_ASSERT_EQUAL_INT(100, tl.getHeightCm());
    TEST_ASSERT_EQUAL_INT(10, tl.getMinHeightCm());
    TEST_ASSERT_EQUAL_INT(4, tl.getLevels());
} 
