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
#define BRIGHTNESS 20
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

    void setAll(byte red, byte green, byte blue) {
        for(int i = 0; i < NUM_LEDS; i++ ) {
            setPixel(i, red, green, blue);
        }
        showStrip();
    }

    void showStrip() {
        FastLED.show();
    }

    void setBrightness(uint8_t scale) {
         FastLED.setBrightness(scale);
         FastLED.show();
    }

    void setPixel(int Pixel, byte red, byte green, byte blue) {
        leds[Pixel].r = red;
        leds[Pixel].g = green;
        leds[Pixel].b = blue;
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
};

#endif //NOTIFICATION_MATRIX_MATRIX_H
