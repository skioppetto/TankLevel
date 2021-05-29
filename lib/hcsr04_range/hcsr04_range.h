class HCSR04Range
{
private:
    int trig, echo;
public:
    HCSR04Range(int trig, int echo);
    ~HCSR04Range();
    void trigger(); // fire a 10us pulse on trigger output
    bool isReady(); // true when a new measure is ready, false if no reponse was received from sensor
};
