//#define BLYNK_PRINT Serial
#define HCSR04_TRIGGER_PIN 0
#define HCSR04_ECHO_PIN 2
#define READING_FREQUENCY_MS 5000ul
#define DEFAULT_HEIGHT 100
#define DEFAULT_NR_LEVELS 7

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "secrets.h"
#include <tank_level.h>
#include <hcsr04_range.h>

// moved to secrets.h file
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "";
//char pass[] = "";

TankLevel tl(DEFAULT_HEIGHT, DEFAULT_NR_LEVELS);
HCSR04Range hc(HCSR04_TRIGGER_PIN, HCSR04_ECHO_PIN);
int last_sent = 0;
WidgetLED ledReady(V2);
void setup()
{
// Debug console
#ifdef DEBUG
  Serial.begin(9600);
#endif
  tl.setMinHeight(5);
  tl.setHysteresis(3);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  hc.trigger();
  if (millis() >= (last_sent + READING_FREQUENCY_MS) /* && hc.isReady() */)
  {
    tl.setMeasure(hc.getDistanceCm());
    if (hc.isReady())
    {
      ledReady.on();
      Blynk.virtualWrite(V0, hc.getDistanceCm());
      Blynk.virtualWrite(V1, tl.getLevel());
    }
    else
    {
      ledReady.off();
    }
#ifdef DEBUG
    Serial.print("distance: ");
    Serial.print(hc.getDistanceCm());
    Serial.print("\tlevel: ");
    Serial.print(tl.getLevel());
    Serial.print("\tinterval: ");
    Serial.println(hc.getIntervalMicros());
#endif
    last_sent = millis();
  }
}