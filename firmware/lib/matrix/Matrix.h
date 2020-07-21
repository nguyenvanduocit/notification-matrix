#ifndef NOTIFICATION_MATRIX_MATRIX_H
#define NOTIFICATION_MATRIX_MATRIX_H

#define FASTLED_ESP8266_RAW_PIN_ORDER
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#define FASTLED_ESP8266_D1_PIN_ORDER
#define FASTLED_INTERNAL
#include <FastLED.h>

#define LED_PIN 3
#define COLOR_ORDER GRB
#define CHIPSET WS2811
#define BRIGHTNESS 5
#define NUM_LEDS 64

#define kMatrixWidth  8
#define kMatrixHeight 8
const bool kMatrixSerpentineLayout = false;

class Matrix {
public:
    CRGBArray<NUM_LEDS> leds;
    void setup()
    {
        FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
        FastLED.setBrightness(BRIGHTNESS);

        leds.fill_solid(0x000000);
        FastLED.show();
    }

    void setBrightness(uint8_t scale) {
         FastLED.setBrightness(scale);
         FastLED.show();
    }

    uint16_t XY(uint8_t x, uint8_t y)
    {
        uint16_t i;

        if( kMatrixSerpentineLayout == false) {
            i = (y * kMatrixWidth) + x;
        }

        if( kMatrixSerpentineLayout == true) {
            if( y & 0x01) {
            // Odd rows run backwards
            uint8_t reverseX = (kMatrixWidth - 1) - x;
            i = (y * kMatrixWidth) + reverseX;
            } else {
            // Even rows run forwards
            i = (y * kMatrixWidth) + x;
            }
        }

        return i;
    }

    void loadingAnimation(unsigned long wait)
    {
        for (uint8_t i = 0; i < NUM_LEDS; i++)
        {
            leds[i] = CHSV(random8(), 255, 255);
            FastLED.show();
            leds[i] = 0x000000;
            delay(wait);
        }
        FastLED.show();
    }

    void turnOnPixel(uint8_t index, int8_t nr, uint8_t ng, uint8_t nb) {
        leds[index].r = nr;
        leds[index].g = ng;
        leds[index].b = nb;
        FastLED.show();
    }

    void successAnimation(unsigned long wait, uint8_t times)
    {
        for (uint8_t i = 0; i < 3; i++)
        {
            leds.fill_gradient(CHSV(random8(), 255, 255), CHSV(random8(), 255, 255));
            FastLED.show();
            FastLED.delay(wait);

            leds.fill_solid(0x000000);
            FastLED.show();
            delay(wait);
        }
    }

    void errorAnimation(unsigned long wait, uint8_t times)
    {
        for (uint8_t i = 0; i < times; i++)
        {
            leds.fill_solid(CRGB::Red);
            FastLED.show();
            delay(wait);

            leds.fill_solid(0x000000);
            FastLED.show();
            delay(wait);
        }
    }
};

#endif //NOTIFICATION_MATRIX_MATRIX_H
