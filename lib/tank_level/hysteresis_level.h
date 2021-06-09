class HysteresisLevel
{
private:
    int hiLevel, loLevel;
public:
    static const int DEFAULT_THRESHOLD = 5; 
    static const int LEVEL_UNCHANGED = 0;
    static const int LEVEL_LOW = -1;
    static const int LEVEL_HIGH = 1;
    HysteresisLevel();
    HysteresisLevel(int level, int threshold); // threshold used to evaluate upper and lower level in hysteresis
    int eval(int measure);
    void setLevel(int level, int threshold);
};