#include<Arduino.h>
#include<hcsr04_range.h>

const int HCSR04_TRIGGER_PIN =3;
const int HCSR04_ECHO_PIN = 4;

HCSR04Range hc(HCSR04_TRIGGER_PIN, HCSR04_ECHO_PIN);

void setup(){
    Serial.begin(9600);
}

unsigned long last;

void loop(){
    hc.trigger();
    if (hc.isReady()){
        last = millis();
        Serial.print("was ready, range uS: ");
        Serial.println(hc.getIntervalMicros());
    }else{
        unsigned long diff = millis() - last;
        Serial.print("not ready, should be less than 60ms: ");
        Serial.println(diff);
    }
    delay(10);
}