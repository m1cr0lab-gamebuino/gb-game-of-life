#ifndef GAME_OF_LIFE_LIGHT_H_
#define GAME_OF_LIFE_LIGHT_H_

#include "bootstrap.h"

class Light
{
    private:

        static const uint8_t FX_NONE;
        static const uint8_t FX_FLASH;
        static const uint8_t FX_BREATHE;

        float hue;
        float saturation;
        float brightness;

        uint8_t fx;
        uint8_t clock;
        float duration;
        bool breatheIn;

        void flashLoop();
        void breatheLoop();
        float easeInOutQuad(float t, float b, float c, float d);
        float easeOutCubic(float t, float b, float c, float d);

    public:

        Light();
        
        float getHue();
        float getSaturation();
        float getBrightness();
        void loop();
        void off();
        void flash(float hue, float duration);
        void breathe(float hue, float period);
        
};

#endif