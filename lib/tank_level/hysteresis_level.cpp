#include <hysteresis_level.h>

HysteresisLevel::HysteresisLevel(){}

HysteresisLevel::HysteresisLevel(int level, int threshold){
    setLevel(level, threshold);
}

int HysteresisLevel::eval(int measure){
    if (measure < this->loLevel)
        return LEVEL_LOW;
    else if (measure > this->hiLevel)
        return LEVEL_HIGH;
    else 
        return LEVEL_UNCHANGED;
}

void HysteresisLevel::setLevel(int level, int threshold){
    this->hiLevel = level + threshold;
    this->loLevel = level - threshold;
}