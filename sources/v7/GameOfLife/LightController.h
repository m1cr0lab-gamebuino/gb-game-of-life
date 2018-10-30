#ifndef GAME_OF_LIFE_LIGHT_CONTROLLER_H_
#define GAME_OF_LIFE_LIGHT_CONTROLLER_H_

#include "bootstrap.h"
#include "Light.h"
#include "LightView.h"

class LightController
{
    private:

        Light* model;
        LightView* view;

    public:

        LightController(Light* model, LightView* view);
        
        void begin();
        void loop();
        void off();
        void flash(float hue, float duration);
        void breathe(float hue, float period);
};

#endif