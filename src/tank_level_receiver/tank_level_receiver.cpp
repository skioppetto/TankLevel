#include <Arduino.h>
#include <radio_message.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN 10

RH_ASK driver;
RadioMessage rmReceived;
Adafruit_NeoPixel strip(7, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void colorWipe(uint32_t c, uint8_t wait, unsigned int pixels)
{
  strip.clear();
  for (uint16_t i = 0; i < strip.numPixels(); i++)
  {
    if (i > 0)
    {
      if (i <= pixels)
        strip.setPixelColor(i, strip.Color(255, 0, 0));
      else
        strip.setPixelColor(i, strip.Color(0, 00, 0));
    }
    strip.show();
    delay(wait);
  }
}

void status_waiting()
{
  strip.setPixelColor(0, strip.Color(0, 0, 0));
  strip.show();
}
void status_receiving()
{
  strip.setPixelColor(0, strip.Color(0, 255, 0));
  strip.show();
}

void status_error()
{
  strip.setPixelColor(0, strip.Color(255, 0, 0));
  strip.show();
}

void setup()
{
#ifdef DEBUG
  Serial.begin(9600);
#endif
  status_error();
  if (driver.init())
  {  
    status_waiting();
  }
  strip.begin();
  strip.setBrightness(50);
  strip.clear(); // Initialize all pixels to 'off'
}

unsigned char last_UID = 0;

void loop()
{
  uint8_t msg[rmReceived.getSize()];
  uint8_t size = sizeof(msg);
  if (driver.recv(msg, &size))
  {
    status_receiving();
    rmReceived.decode(msg);
    if (last_UID != rmReceived.getUID())
    {
      colorWipe(strip.Color(255, 0, 0), 50, rmReceived.getValue());
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
    status_waiting();
  }
}