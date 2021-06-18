#include <Arduino.h>
#include <hcsr04_range.h>

const int HCSR04_TRIGGER_PIN =3;
const int HCSR04_ECHO_PIN = 4;

HCSR04Range hc(HCSR04_TRIGGER_PIN, HCSR04_ECHO_PIN);

void setup(){
    Serial.begin(9600);
}

void loop(){
    hc.trigger();
    if (hc.isReady()){
        Serial.print (hc.getIntervalMicros());
        Serial.print( " us;\t");
        Serial.print (hc.getDistanceCm());
        Serial.print( " cm;\t");
        Serial.print (hc.getDistanceInches());
        Serial.println( " inches;");
        
    }
    delay(1000);
}