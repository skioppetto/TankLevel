#ifndef POC_NATIVE
const unsigned int HCSR04_MIN_CYCLE_MS = 60;
class HCSR04Range
{
private:
    int trig, echo;
    bool ready;
    unsigned long last_measure_ms; // used for min. measurement cycle (#11) 
    unsigned long interval;
    bool checkMinCycle();
public:
    HCSR04Range(int trig, int echo);
    ~HCSR04Range();
    void trigger(); // fire a 10us pulse on trigger output
    bool isReady(); // true when a new measure is ready, false if no reponse was received from sensor or less then suggested minimum measurement cycle (60ms) 
    unsigned long getIntervalMicros(); // return echo interval in microseconds
    unsigned int getDistanceCm();
    unsigned int getDistanceInches();
};
#endif