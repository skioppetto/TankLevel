#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLSPYggA0t"
#define BLYNK_DEVICE_NAME "TankLevel Transmitter"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "secrets.h"


// moved to secrets.h file
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "";
//char pass[] = "";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}