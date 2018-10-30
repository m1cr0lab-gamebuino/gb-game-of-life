#include "AutomatonController.h"

AutomatonController::AutomatonController(Automaton* model, AutomatonView* view) : model(model), view(view) {

}

void AutomatonController::begin() {
    this->randomize();
    this->view->draw();
}

void AutomatonController::spawn(size_t x, size_t y) {
    this->model->spawn(x, y);
}

void AutomatonController::kill(size_t x, size_t y) {
    this->model->kill(x, y);
}

void AutomatonController::clear() {
    this->model->clear();
}

void AutomatonController::randomize() {
    this->model->randomize();
}

void AutomatonController::loop() {
    this->step();
}

void AutomatonController::step() {
    this->model->step();
    this->view->draw();
}

void AutomatonController::update() {
    this->view->draw();
}