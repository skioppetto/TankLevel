class TankLevel
{
private:
    /* data */
    int heightCm, minHeightCm, levels, measure;
public:
    TankLevel(/* args */);
    ~TankLevel();
    void setHeightCm(int);
    int getHeightCm();
    void setMinHeightCm(int);
    int getMinHeightCm();
    void setLevels(int);
    int getLevels();
    void setMeasure(int);
    int getMeasure();
};