#include "LightView.h"
#include "bootstrap.h"

LightView::LightView(Light* model) : model(model) {

}

void LightView::draw() {
    float h = this->model->getHue();
    float s = this->model->getSaturation();
    float b = this->model->getBrightness();
    Color color = this->createColor(h, s, b);
    gb.lights.fill(color);
}

Color LightView::createColor(float hue, float saturation, float brightness) {
    float r = 0, g = 0, b = 0;
    float v = brightness;

    if (saturation == 0.0) {
        r = v;
        g = v;
        b = v;
    } else {
        int i;
        float f, p, q, t;
        if (hue == 360.0) { hue = 0; } else { hue /= 60; }
        i = (int)trunc(hue);
        f = hue - i;
        p = v * (1.0 - saturation);
        q = v * (1.0 - f * saturation);
        t = v * (1.0 - (1.0 - f) * saturation);

        switch (i) {
            case 0:  r = v; g = t; b = p; break;
            case 1:  r = q; g = v; b = p; break;
            case 2:  r = p; g = v; b = t; break;
            case 3:  r = p; g = q; b = v; break;
            case 4:  r = t; g = p; b = v; break;
            default: r = v; g = p; b = q;
        }
    }

    int red   = (uint8_t)(r * 255);
    int green = (uint8_t)(g * 255);
    int blue  = (uint8_t)(b * 255);

    return gb.createColor(red, green, blue);
}