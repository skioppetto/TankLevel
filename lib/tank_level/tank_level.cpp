#include<tank_level.h>

TankLevel::TankLevel(/* args */)
{
}

TankLevel::~TankLevel()
{
}

void TankLevel::setHeightCm(int hc){heightCm = hc;}
void TankLevel::setMinHeightCm(int mhc){minHeightCm = mhc;}
void TankLevel::setLevels(int l){levels = l;}
void TankLevel::setMeasure(int m){measure = m;}
int TankLevel::getHeightCm(){return heightCm;}
int TankLevel::getMinHeightCm(){return minHeightCm;}
int TankLevel::getLevels(){return levels;}
int TankLevel::getMeasure(){return measure;}
int TankLevel::getLevel(){return 0;}
