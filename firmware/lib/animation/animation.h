#ifndef NOTIFICATION_MATRIX_ANIMATION_H
#define NOTIFICATION_MATRIX_ANIMATION_H

#include <Matrix.h>
#include <FastLED.h>

class Animation {
    private:
      Matrix *matrix;
    public:
    Animation(Matrix *matr) {
        matrix = matr;
    }

    void loadingAnimation(unsigned long wait)
    {
        for (uint8_t i = 0; i < NUM_LEDS; i++)
        {
            matrix->leds[i] = CHSV(random8(), 255, 255);
            FastLED.show();
            matrix->showStrip();
            matrix->leds[i] = 0x000000;
            delay(wait);
        }
        FastLED.show();
    }

    void turnOnPixel(uint8_t index, int8_t nr, uint8_t ng, uint8_t nb) {
        matrix->leds[index].r = nr;
        matrix->leds[index].g = ng;
        matrix->leds[index].b = nb;
        matrix->showStrip();
    }

    void successAnimation(unsigned long wait, uint8_t times)
    {
        for (uint8_t i = 0; i < 3; i++)
        {
            matrix->leds.fill_gradient(CHSV(random8(), 255, 255), CHSV(random8(), 255, 255));
            matrix->showStrip();
            FastLED.delay(wait);

            matrix->leds.fill_solid(0x000000);
            matrix->showStrip();
            delay(wait);
        }
    }

    void errorAnimation(unsigned long wait, uint8_t times)
    {
        for (uint8_t i = 0; i < times; i++)
        {
            matrix->leds.fill_solid(CRGB::Red);
            matrix->showStrip();
            delay(wait);

            matrix->leds.fill_solid(0x000000);
            matrix->showStrip();
            delay(wait);
        }
    }

    //Strobe(0xff, 0xff, 0xff, 10, 50, 1000);
    void strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause){
        for(int j = 0; j < StrobeCount; j++) {
            matrix->setAll(red,green,blue);
            matrix->showStrip();
            delay(FlashDelay);
            matrix->setAll(0,0,0);
            matrix->showStrip();
            delay(FlashDelay);
        }
        
        delay(EndPause);
    }

    //cylonBounce(0xff, 0, 0, 4, 10, 50);
    void cylonBounce(int EyeSize, int SpeedDelay, int ReturnDelay){
        for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
            byte red = random(255);
            byte blue = random(255);
            byte green = random(255);
            matrix->setAll(0,0,0);
            matrix->setPixel(i, red/20, green/20, blue/20);
            for(int j = 1; j <= EyeSize; j++) {
                matrix->setPixel(i+j, red, green, blue);
            }
            matrix->setPixel(i+EyeSize+1, red/20, green/20, blue/20);
            matrix->showStrip();
            delay(SpeedDelay);
        }

        delay(ReturnDelay);

        for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
            byte red = random(255);
            byte blue = random(255);
            byte green = random(255);
            matrix->setAll(0,0,0);
            matrix->setPixel(i, red/20, green/20, blue/20);
            for(int j = 1; j <= EyeSize; j++) {
                matrix->setPixel(i+j, red, green, blue);
            }
            matrix->setPixel(i+EyeSize+1, red/20, green/20, blue/20);
            matrix->showStrip();
            delay(SpeedDelay);
        }

        delay(ReturnDelay);
        
    }

    void sparkle(byte red, byte green, byte blue, int SpeedDelay) {
        int Pixel = random(NUM_LEDS);
        matrix->setPixel(Pixel,red,green,blue);
        matrix->showStrip();
        delay(SpeedDelay);
        matrix->setPixel(Pixel, 0,0,0);
    }
};
#endif //NOTIFICATION_MATRIX_ANIMATION_H