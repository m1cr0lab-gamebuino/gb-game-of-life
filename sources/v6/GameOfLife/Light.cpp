#include "Light.h"

const uint8_t Light::FX_NONE    = 0;
const uint8_t Light::FX_FLASH   = 1;
const uint8_t Light::FX_BREATHE = 2;

Light::Light() {
    this->hue = 0;
    this->saturation = 1;
    this->brightness = 0;
    this->fx = FX_NONE;
    this->clock = 0;
    this->duration = 1;
    this->breatheIn = true;
}

float Light::getHue() {
    return this->hue;
}

float Light::getSaturation() {
    return this->saturation;
}

float Light::getBrightness() {
    return this->brightness;
}

void Light::loop() {
    switch (this->fx) {
        case FX_FLASH:
            this->flashLoop();
            break;
        case FX_BREATHE:
            this->breatheLoop();
            break;
    }
}

void Light::flashLoop() {
    float t = (float)this->clock++;
    this->brightness = this->easeOutCubic(t, 1.0, -1.0, this->duration);

    if (this->clock >= this->duration) {
        this->off();
    }
}

void Light::breatheLoop() {
    float t = (float)this->clock++;
    float b = this->breatheIn ? 0.0 :  1.0;
    float c = this->breatheIn ? 1.0 : -1.0;
    this->brightness = this->easeInOutQuad(t, b, c, this->duration);

    if (this->clock >= this->duration) {
        this->clock = 0;
        this->breatheIn = !this->breatheIn;
    }
}

void Light::off() {
    this->fx = FX_NONE;
    this->brightness = 0;
}

void Light::flash(float hue, float duration) {
    this->fx = FX_FLASH;
    this->hue = hue;
    this->clock = 0;
    this->duration = duration * 25.0;
}

void Light::breathe(float hue, float period) {
    this->fx = FX_BREATHE;
    this->hue = hue;
    this->clock = 0;
    this->duration = period * .5 * 25.0;
    this->breatheIn = true;
}

float Light::easeInOutQuad(float t, float b, float c, float d) {
    t /= d/2;
	if (t < 1) return c/2*t*t + b;
	t--;
	return -c/2 * (t*(t-2) - 1) + b;
}

float Light::easeOutCubic(float t, float b, float c, float d) {
    t /= d;
	t--;
	return c*(t*t*t + 1) + b;
}