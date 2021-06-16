#include <hysteresis_level.h>
class TankLevel
{
private:
    /* data */
    int height, minHeight, levels, measure, step, hysteresis, currentLevel;
    HysteresisLevel *hystersisLevels; // hold hysteresis level logic for each level
    void calculateStep();    // calculate step based on height and nr of levels 
    void calculateHysteresis(); // calculate hysteresis if a value was set
    int calculateLevel(); // calculate the current level
public:
    static const int LEVEL_LOW = 0;
    static const int LEVEL_OVERFLOW = -1;
    TankLevel(int height, int levels);
    ~TankLevel();
    void setHeight(int);
    int getHeight();
    void setMinHeight(int);
    int getMinHeight();
    void setLevels(int);
    int getLevels();
    void setMeasure(int);
    int getMeasure();
    int getLevel();
    void setHysteresis(int);
};