#include <Arduino.h>
#include <hcsr04_range.h>
#include <tank_level.h>
const int HCSR04_TRIGGER_PIN =3;
const int HCSR04_ECHO_PIN = 4;

HCSR04Range hc(HCSR04_TRIGGER_PIN, HCSR04_ECHO_PIN);
TankLevel tl;

void setup(){
    Serial.begin(9600);
    tl.setHeight(30);
    tl.setMinHeight(5);
    tl.setLevels(3);
    tl.setHysteresis(5);
}

void loop(){
    hc.trigger();
    if (hc.isReady()){
        Serial.print (hc.getIntervalMicros());
        Serial.print( " us;\t");
        int distance = hc.getDistanceCm();
        Serial.print (distance);
        Serial.print( " cm;\t");
        tl.setMeasure(distance);
        Serial.print (tl.getLevel());
        Serial.println( " level;");
        
    }
}