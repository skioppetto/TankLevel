#include<tank_level.h>

TankLevel::TankLevel(/* args */)
{
}

TankLevel::~TankLevel()
{
    this->levels = 1;   // init this value to avoid div by 0 in step calculation 
    calculateStep();
}

void TankLevel::setHeightCm(int hc){heightCm = hc; calculateStep();}
void TankLevel::setMinHeightCm(int mhc){minHeightCm = mhc;}
void TankLevel::setLevels(int l){levels = l; calculateStep();}
void TankLevel::setMeasure(int m){measure = m;}
int TankLevel::getHeightCm(){return heightCm;}
int TankLevel::getMinHeightCm(){return minHeightCm;}
int TankLevel::getLevels(){return levels;}
int TankLevel::getMeasure(){return measure;}
int TankLevel::getLevel(){
    if (measure > (heightCm - minHeightCm))
        return 0;
    else 
        return ((heightCm - measure) / step) + 1;
}
void TankLevel::calculateStep(){this->step = heightCm / levels; }