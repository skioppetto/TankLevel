#include <Adafruit_NeoPixel.h>

#ifdef ESP8266 
#define NEOPIXEL_PIN 0
#else
#define NEOPIXEL_PIN 10
#endif

Adafruit_NeoPixel strip(7, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void strip_setup()
{
    strip.begin();
    strip.setBrightness(50);
    strip.clear(); // Initialize all pixels to 'off'
}

void strip_colorWipe(uint32_t c, uint8_t wait, unsigned int pixels)
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

void strip_status_sleep()
{
    strip.clear();
    strip.show();
}

void strip_status_waiting()
{
    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();
}
void strip_status_receiving()
{
    strip.setPixelColor(0, strip.Color(0, 255, 0));
    strip.show();
}

void strip_status_error()
{
    strip.setPixelColor(0, strip.Color(255, 0, 0));
    strip.show();
}
