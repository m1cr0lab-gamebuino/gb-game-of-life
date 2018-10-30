#include "LightController.h"

LightController::LightController(Light* model, LightView* view) : model(model), view(view) {

}

void LightController::begin() {
    
}

void LightController::loop() {
    this->model->loop();
    this->view->draw();
}

void LightController::off() {
    this->model->off();
    this->view->draw();
}

void LightController::flash(float hue, float duration) {
    this->model->flash(hue, duration);
}

void LightController::breathe(float hue, float period) {
    this->model->breathe(hue, period);
}