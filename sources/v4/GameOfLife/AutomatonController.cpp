#include "AutomatonController.h"

AutomatonController::AutomatonController(Automaton* model, AutomatonView* view) : model(model), view(view) {

}

void AutomatonController::begin() {
    this->randomize();
}

void AutomatonController::randomize() {
    this->model->randomize();
}

void AutomatonController::loop() {
    this->model->step();
    this->view->draw();
}