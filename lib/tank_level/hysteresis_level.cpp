#include <hysteresis_level.h>

HysteresisLevel::HysteresisLevel(){}

HysteresisLevel::HysteresisLevel(int level, int threshold){
    setLevel(level, threshold);
}

int HysteresisLevel::eval(int measure){
    if (measure < this->loLevel)
        return LOW;
    else if (measure > this->hiLevel)
        return HIGH;
    else 
        return UNCHANGED;
}

void HysteresisLevel::setLevel(int level, int threshold){
    this->hiLevel = level + threshold;
    this->loLevel = level - threshold;
}