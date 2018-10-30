#include "bootstrap.h"
#include "UserController.h"
#include "GameController.h"

const char* UserController::MAIN_MENU[] = {
    "CLEAR",
    "EDIT",
    "RANDOMIZE",
    "PATTERNS",
    "EXIT"
};

UserController::UserController(GameController* gameController) : gameController(gameController) {

}

void UserController::begin() {
    
}

void UserController::loop() {
    GameController* gc = this->gameController;

    if (gb.buttons.pressed(BUTTON_MENU)) {
        if (gc->isEditing()) {
            gc->stopEdit();
            gc->update();
        } else {
            gc->lightOff();
            this->openMainMenu();
        }
    } else {
        this->checkButtons();
    }
}

void UserController::checkButtons() {
    GameController* gc = this->gameController;

    if (gc->isWaiting()) {

        if (gb.buttons.pressed(BUTTON_A)) {
            gc->start();
        } else if (gb.buttons.pressed(BUTTON_B)) {
            gc->step();
        } else if (gb.buttons.repeat(BUTTON_B, 3)) {
            gc->step();
        }

    } else if (!gc->isEditing()) {

        if (gb.buttons.pressed(BUTTON_B)) {
            gc->stop();
        }

    }
}

void UserController::openMainMenu() {
    GameController* gc = this->gameController;
    gc->stop();
    
    uint8_t selected = gb.gui.menu("SELECT AN OPTION:", MAIN_MENU);

    switch (selected) {
        case 0:
            gc->clear();
            break;
        case 1:
            gc->startEdit();
            break;
        case 2:
            gc->randomize();
            break;
    }

    gc->update();
}