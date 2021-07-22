extern "C"
{
#include "user_interface.h"
}

#define RTC_START_MEMORY 65
#ifdef DEBUG
#define BLYNK_PRINT Serial
#endif
#define HCSR04_TRIGGER_PIN 14 //D5
#define HCSR04_ECHO_PIN 12    //D6
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
int currentLevel = -1, level;
unsigned long timeout_last_millis;
const unsigned int HC_TIMEOUT_MILLIS = 2000;
const unsigned int CONN_TIMEOUT_MILLIS = 5000;
bool connected = false;

void setup()
{
  tl.setMinHeight(5);
  tl.setHysteresis(3);
  system_rtc_mem_read(RTC_START_MEMORY, &currentLevel, sizeof(int));
  // Debug console
#ifdef DEBUG
  Serial.begin(9600);
  Serial.print("currentLevel: ");
  Serial.println(currentLevel);
#endif
  if (currentLevel >= 0 && currentLevel <= tl.getLevels())
    tl.setCurrentLevel(currentLevel);
  timeout_last_millis = millis();
  while (millis() < timeout_last_millis + HC_TIMEOUT_MILLIS)
  {
    hc.trigger();
    if (hc.isReady())
    {
      tl.setMeasure(hc.getDistanceCm());
      level = tl.getLevel();
      #ifdef DEBUG
      Serial.print("distance: ");
      Serial.print(hc.getDistanceCm());
      Serial.print("\tlevel: ");
      Serial.print(level);
      Serial.print("\tinterval: ");
      Serial.println(hc.getIntervalMicros());
      #endif
      if (level != currentLevel)
      {
        Blynk.connectWiFi(ssid, pass); // Blynk WiFi setup
        Blynk.config(auth);
        connected = Blynk.connect(CONN_TIMEOUT_MILLIS);
      }else{
        break;
      }
    }
  }
  #ifdef DEBUG
  Serial.begin(9600);
  Serial.print("connected: ");
  Serial.println(connected);
  #endif
  if (!connected)
    ESP.deepSleep(10e6);
}

void loop()
{
  Blynk.run();

  if (level >= 0)
    ledReady.on();
  else
    ledReady.off();

  Blynk.virtualWrite(V0, hc.getDistanceCm());
  Blynk.virtualWrite(V1, level);
  currentLevel = level;
  system_rtc_mem_write(RTC_START_MEMORY, &currentLevel, sizeof(int));

  ESP.deepSleep(10e6);
}