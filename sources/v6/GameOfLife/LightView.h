#ifndef GAME_OF_LIFE_LIGHT_VIEW_H_
#define GAME_OF_LIFE_LIGHT_VIEW_H_

#include "bootstrap.h"
#include "Light.h"

class LightView
{
    private:

        Light* model;

        Color createColor(float hue, float saturation, float brightness);

    public:

        LightView(Light* model);
        
        void draw();
};

#endif