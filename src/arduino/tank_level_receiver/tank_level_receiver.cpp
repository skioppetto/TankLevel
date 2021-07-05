#include <Arduino.h>
#include <radio_message.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#include <tank_level_msg.h>
#include "common_receiver.cpp"
#include <LowPower.h>

#define WAKEUP_PIN 2

RH_ASK driver;
RadioMessage rmReceived;

void setup()
{
#ifdef DEBUG
  Serial.begin(9600);
#endif
  strip_status_error();
  if (driver.init())
  {
    strip_status_waiting();
  }
  strip_setup();
  pinMode(WAKEUP_PIN, INPUT_PULLUP);
}

unsigned char last_UID = 0;
unsigned char last_value = 0;
unsigned long wake_up_time = 0;
unsigned int WAKE_UP_DURATION = 8000;

void wakeUp(){
  wake_up_time = millis();
  strip_status_receiving();
}

void loop()
{
  if (millis() - wake_up_time > WAKE_UP_DURATION){
    strip_status_sleep();
    /*go to sleep*/
    attachInterrupt(digitalPinToInterrupt(WAKEUP_PIN), wakeUp, LOW);
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF,BOD_OFF);
    /*needed after wakeup*/
    detachInterrupt(digitalPinToInterrupt(WAKEUP_PIN));   
  }
  uint8_t msg[rmReceived.getSize()];
  uint8_t size = sizeof(msg);
  if (driver.recv(msg, &size))
  {
    rmReceived.decode(msg);
    if (rmReceived.getType() == TANK_LEVEL_MSG_TYPE && rmReceived.getKey() == TANK_LEVEL_MSG_LEVEL_KEY)
    {
      if (last_UID != rmReceived.getUID())
      {
        if (last_value != rmReceived.getValue()){
          strip_colorWipe(strip.Color(255, 0, 0), 50, rmReceived.getValue());
          last_value = rmReceived.getValue();
        }
        last_UID = rmReceived.getUID();
#ifdef DEBUG
        Serial.print("Message received:: UID: ");
        Serial.print(rmReceived.getUID());
        Serial.print("\ttype: ");
        Serial.print(rmReceived.getType());
        Serial.print("\tprogressive: ");
        Serial.print(rmReceived.getProgressive());
        Serial.print("\tkey: ");
        Serial.print(rmReceived.getKey());
        Serial.print("\tvalue: ");
        Serial.println(rmReceived.getValue());
#endif
      }
      else
      {
#ifdef DEBUG
        Serial.print("Message skipped:: UID: ");
        Serial.println(rmReceived.getUID());
#endif
      }
    }
  }
}