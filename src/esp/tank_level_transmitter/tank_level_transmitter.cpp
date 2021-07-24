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
WidgetLED ledReady(V2);
int currentLevel = -1;
unsigned long timeout_last_count;
const unsigned int HC_TIMEOUT_MILLIS = 2000;
const unsigned int CONN_TIMEOUT_MILLIS = 5000;
const unsigned int DEEP_SLEEP_TIMEOUT_MICROS = 20e6;
const unsigned int SEND_ANYWAY_COUNT = 5*60e6 / DEEP_SLEEP_TIMEOUT_MICROS;
bool connected = false;
const int CURRENT_LEVEL_ADDR = RTC_START_MEMORY;
const int SEND_ANYWAY_COUNT_ADDR = RTC_START_MEMORY + sizeof(int);

void setup()
{
  int level;

  pinMode(A0, INPUT);

  tl.setMinHeight(5);
  tl.setHysteresis(3);
  system_rtc_mem_read(CURRENT_LEVEL_ADDR, &currentLevel, sizeof(int));
  system_rtc_mem_read(SEND_ANYWAY_COUNT_ADDR, &timeout_last_count, sizeof(int));
  // Debug console
#ifdef DEBUG
  Serial.begin(9600);
  Serial.print("currentLevel: ");
  Serial.print(currentLevel);
  Serial.print("\tcount anyway: ");
  Serial.print(timeout_last_count);
  Serial.print(" / ");
  Serial.println(SEND_ANYWAY_COUNT);
#endif
  if (currentLevel >= 0 && currentLevel <= tl.getLevels())
    tl.setCurrentLevel(currentLevel);
  if (timeout_last_count < 0)
    timeout_last_count = 0;
  unsigned long timeout_last_millis = millis();
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
      break;
    }
  }
  if (level != currentLevel || timeout_last_count > SEND_ANYWAY_COUNT)
  {
    Blynk.connectWiFi(ssid, pass); // Blynk WiFi setup
    Blynk.config(auth);
    connected = Blynk.connect(CONN_TIMEOUT_MILLIS);
  }
  (timeout_last_count > SEND_ANYWAY_COUNT) ? timeout_last_count = 0 : timeout_last_count++;
  system_rtc_mem_write(SEND_ANYWAY_COUNT_ADDR, &timeout_last_count, sizeof(int));
#ifdef DEBUG
  Serial.print("connected: ");
  Serial.println(connected);
#endif
  if (connected)
  {
    int raw = analogRead(A0);
    float volt = raw / 1023.0;
    volt = volt * 4.2;
    Blynk.virtualWrite(V1, level);
    (level >= 0) ? ledReady.on() : ledReady.off();
    Blynk.virtualWrite(V0, volt);
#ifdef DEBUG
    Serial.print("message sent: ");
    Serial.print("\tlevel: ");
    Serial.print(level);
    Serial.print("\tvolt: ");
    Serial.println(volt);
#endif
    delay(100);
    currentLevel = level;
    system_rtc_mem_write(CURRENT_LEVEL_ADDR, &currentLevel, sizeof(int));
  }
  ESP.deepSleep(DEEP_SLEEP_TIMEOUT_MICROS);
}

void loop()
{
}