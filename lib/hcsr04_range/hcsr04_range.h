class HCSR04Range
{
private:
    /* data */
public:
    HCSR04Range(int trig, int echo);
    ~HCSR04Range();
    void trigger(); // fire a 10us pulse on trigger output
};
