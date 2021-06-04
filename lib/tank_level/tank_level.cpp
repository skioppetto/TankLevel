#include<tank_level.h>

TankLevel::TankLevel(/* args */)
{
}

TankLevel::~TankLevel()
{
    this->levels = 1;   // init this value to avoid div by 0 in step calculation 
    calculateStep();
}

void TankLevel::setHeight(int hc){height = hc; calculateStep();}
void TankLevel::setMinHeight(int mhc){minHeight = mhc;}
void TankLevel::setLevels(int l){levels = l; calculateStep();}
void TankLevel::setMeasure(int m){measure = m;}
int TankLevel::getHeight(){return height;}
int TankLevel::getMinHeight(){return minHeight;}
int TankLevel::getLevels(){return levels;}
int TankLevel::getMeasure(){return measure;}
int TankLevel::getLevel(){
    if (measure > height)
        return LEVEL_OVERFLOW;
    else if (measure > (height - minHeight))
        return LEVEL_LOW;
    else 
        return ((height - measure) / step) + 1;
}
void TankLevel::calculateStep(){this->step = height / levels; }