class HysteresisLevel
{
private:
    int hiLevel, loLevel;
public:
    static const int DEFAULT_THRESHOLD = 5; 
    static const int UNCHANGED = 0;
    static const int LOW = -1;
    static const int HIGH = 1;
    
    HysteresisLevel(int level, int threshold); // threshold used to evaluate upper and lower level in hysteresis
    int eval(int measure);
};