#include <Arduino.h>
#include "common_receiver.cpp"

#define WAKEUP_PIN 2    // connect button to IO2 and strip to IO0

void setup()
{
#ifdef DEBUG
  Serial.begin(9600);
#endif
  strip_setup();
  pinMode(WAKEUP_PIN, INPUT_PULLUP);
}

unsigned char last_UID = 0;
unsigned char last_value = 0;
unsigned long wake_up_time = 0;
unsigned int WAKE_UP_DURATION = 8000;


void loop()
{
    for (int i=0; i<7; i++){
        strip_colorWipe(strip.Color(255, 0, 0), 50, i);
        delay(250); 
    }
    strip_status_sleep();
    delay(250);
}