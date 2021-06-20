#include <Arduino.h>
#include <tank_level.h>
#include <hcsr04_range.h>
#include <radio_message.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

const int DEFAULT_HEIGHT = 50;
const int DEFAULT_NR_LEVELS = 4; 
const int DEFAULT_MIN_HEIGHT = 5; 
const int DEFAULT_HYSTERESIS = 3;
const int HCSR04_TRIGGER_PIN = 8;
const int HCSR04_ECHO_PIN = 9; 

const int DUPLICATED_MESSAGES = 5;

// Tank Level message types (move to include?)
const unsigned char TANK_LEVEL_MSG_TYPE = 0XA;
const unsigned char TANK_LEVEL_MSG_PROGRESSIVE = 0x01;  // only one tank level in the network
const unsigned char TANK_LEVEL_MSG_LEVEL_KEY = 0X01;    // this key contains the current level
const unsigned char TANK_LEVEL_MSG_CM_KEY = 0X02;       // this key contains the current level in cm 
const unsigned char TANK_LEVEL_MSG_TOF_KEY = 0X03;       // this is the tof of the sensor in us

RadioMessage rmLevel(TANK_LEVEL_MSG_TYPE, TANK_LEVEL_MSG_PROGRESSIVE, TANK_LEVEL_MSG_LEVEL_KEY);

TankLevel tl(DEFAULT_HEIGHT, DEFAULT_NR_LEVELS);
HCSR04Range hc(HCSR04_TRIGGER_PIN, HCSR04_ECHO_PIN);

// RH_ASK (uint16_t speed=2000, uint8_t rxPin=11, uint8_t txPin=12, uint8_t pttPin=10, bool pttInverted=false)
RH_ASK driver;

// last sent level;
unsigned char last_level = 0;

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
    if (current_level >= 0 && current_level != last_level){
      for (int i=0; i<DUPLICATED_MESSAGES; i++){
        driver.send((uint8_t*) rmLevel.encode(current_level), rmLevel.getSize());
        driver.waitPacketSent();
        delay(50);
      }
      rmLevel.newUID(); // increase UID for next message
      last_level = current_level;
      #ifdef DEBUG
      Serial.print("message sent: ");
      Serial.println(current_level); 
      #endif
    }
  }
}