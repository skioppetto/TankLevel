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
int TankLevel::getHeightCm(){return heightCm;}
int TankLevel::getMinHeightCm(){return minHeightCm;}
int TankLevel::getLevels(){return levels;}