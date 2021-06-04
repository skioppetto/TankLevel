class TankLevel
{
private:
    /* data */
    int height, minHeight, levels, measure, step;
    void calculateStep();    // calculate step based on height and nr of levels 
public:
    static const int LEVEL_LOW = 0;
    static const int LEVEL_OVERFLOW = -1;
    TankLevel(/* args */);
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
};