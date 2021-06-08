#include<tank_level.h>

TankLevel::TankLevel(/* args */)
{
}

TankLevel::~TankLevel()
{
    this->levels = 1;       // init this value to avoid div by 0 in step calculation 
    this->hysteresis = 0;   // 0 means no hysteresis required
    this->currentLevel = -1; // need to evaluate if it's the first time level is set
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
    int retLevel;
    if (measure > height)
        retLevel = LEVEL_OVERFLOW;
    else if (measure > (height - minHeight))
        retLevel = LEVEL_LOW;
    else {
        retLevel = ((height - measure) / step) + 1;
    }
    bool unchange = false;
    if (hysteresis && currentLevel >= 0){
        if (retLevel == currentLevel-1 && hystersisLevels[retLevel-1].eval(measure) != HysteresisLevel::HIGH){
            unchange = true;
        }
        if (retLevel == currentLevel+1 && hystersisLevels[currentLevel-1].eval(measure) != HysteresisLevel::LOW){
            unchange = true;
        }
    }
    if (!unchange){
        currentLevel = retLevel;
        return retLevel;
    }else{
        return currentLevel;
    }
}
void TankLevel::calculateStep(){this->step = height / levels; }
void TankLevel::setHysteresis(int h){this->hysteresis = h; calculateHysteresis();}
void TankLevel::calculateHysteresis(){
    hystersisLevels = new HysteresisLevel[this->levels - 1];
    for (int i=this->levels-1, j=1; i >0; i--, j++){
        hystersisLevels[i-1].setLevel(this->step*j, 2);
    }
}