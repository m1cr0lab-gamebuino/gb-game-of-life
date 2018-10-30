#include "EditorController.h"

EditorController::EditorController(Editor* model, EditorView* view, AutomatonController* automatonController) : model(model), view(view), automatonController(automatonController) {
    
}

void EditorController::begin() {
    
}

void EditorController::loop() {
    Editor* m = this->model;
    AutomatonController* ac = this->automatonController;

    if (gb.buttons.repeat(BUTTON_A, 1)) {
        ac->spawn(m->getX(), m->getY());
    } else if (gb.buttons.repeat(BUTTON_B, 1)) {
        ac->kill(m->getX(), m->getY());
    }
    
    if (gb.buttons.repeat(BUTTON_UP, 1)) {
        m->up();
    } else if (gb.buttons.repeat(BUTTON_DOWN, 1)) {
        m->down();
    } else if (gb.buttons.repeat(BUTTON_LEFT, 1)) {
        m->left();
    } else if (gb.buttons.repeat(BUTTON_RIGHT, 1)) {
        m->right();
    }

    this->update();
}

void EditorController::update() {
    this->automatonController->update();
    this->view->draw();
}