#include <Arduino.h>
#include <tank_level.h>
#include <hcsr04_range.h>
#include <radio_message.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <tank_level_msg.h>

const int DEFAULT_HEIGHT = 50;
const int DEFAULT_NR_LEVELS = 6; 
const int DEFAULT_MIN_HEIGHT = 5; 
const int DEFAULT_HYSTERESIS = 3;
const int HCSR04_TRIGGER_PIN = 8;
const int HCSR04_ECHO_PIN = 9; 

const int DUPLICATED_MESSAGES = 3;
const int DUPLICATED_MESSAGES_DELAY = 100; // ms between resent messages
const int RESEND_TIMEOUT = 2000; 


RadioMessage rmLevel(TANK_LEVEL_MSG_TYPE, TANK_LEVEL_MSG_PROGRESSIVE, TANK_LEVEL_MSG_LEVEL_KEY);

TankLevel tl(DEFAULT_HEIGHT, DEFAULT_NR_LEVELS);
HCSR04Range hc(HCSR04_TRIGGER_PIN, HCSR04_ECHO_PIN);

// RH_ASK (uint16_t speed=2000, uint8_t rxPin=11, uint8_t txPin=12, uint8_t pttPin=10, bool pttInverted=false)
RH_ASK driver;

// last sent level;
unsigned char last_level = 0;
unsigned long last_sent = 0;
void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  driver.init();
  tl.setMinHeight(DEFAULT_MIN_HEIGHT);
  tl.setHysteresis(DEFAULT_HYSTERESIS);
}

void loop() {
  hc.trigger();
  if (hc.isReady()){
    tl.setMeasure(hc.getDistanceCm());
    int current_level = tl.getLevel();
    if (current_level >= 0 && (current_level != last_level || (millis()-last_sent) > RESEND_TIMEOUT)){
      for (int i=0; i<DUPLICATED_MESSAGES; i++){
        driver.send((uint8_t*) rmLevel.encode(current_level), rmLevel.getSize());
        driver.waitPacketSent();
        delay(DUPLICATED_MESSAGES_DELAY);
      }
      rmLevel.newUID(); // increase UID for next message
      last_level = current_level;
      last_sent = millis();
      #ifdef DEBUG
      Serial.print("message sent: ");
      Serial.println(current_level); 
      #endif
    }
  }
}