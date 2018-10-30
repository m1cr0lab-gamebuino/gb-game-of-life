#include "GameController.h"

const uint8_t GameController::STATE_SUSPENDED = 0;
const uint8_t GameController::STATE_RUNNING   = 1;
const uint8_t GameController::STATE_EDITING   = 2;

GameController::GameController() : state(STATE_SUSPENDED) {
    this->initAutomatonController();
    this->initEditorController();
    this->initLightController();
    this->initSoundController();
    this->initUserController();
}

void GameController::initAutomatonController() {
    Automaton* automaton = new Automaton();
    AutomatonView* automatonView = new AutomatonView(automaton);
    this->automatonController = new AutomatonController(automaton, automatonView);
}

void GameController::initEditorController() {
    Editor* editor = new Editor(W/2, H/2);
    EditorView* editorView = new EditorView(editor);
    this->editorController = new EditorController(editor, editorView, this->automatonController);
}

void GameController::initLightController() {
    Light* light = new Light();
    LightView* lightView = new LightView(light);
    this->lightController = new LightController(light, lightView);
}

void GameController::initSoundController() {
    this->soundController = new SoundController();
}

void GameController::initUserController() {
    this->userController = new UserController(this);
}

void GameController::begin() {
    this->automatonController->begin();
    this->editorController->begin();
    this->lightController->begin();
    this->userController->begin();

    this->start();
}

void GameController::loop() {
    this->lightController->loop();
    this->userController->loop();

    if (this->state == STATE_RUNNING) {
        this->automatonController->loop();
    } else if (this->state == STATE_EDITING) {
        this->editorController->loop();
    }
}

void GameController::clear() {
    this->automatonController->clear();
}

void GameController::randomize() {
    this->automatonController->randomize();
}

void GameController::addPattern(const uint8_t* pattern, uint8_t x, uint8_t y) {
    this->automatonController->addPattern(pattern, x, y);
}

void GameController::start() {
    this->state = STATE_RUNNING;
    this->soundController->playStart();
    this->lightController->breathe(100, .5);
}

void GameController::stop() {
    this->state = STATE_SUSPENDED;
    this->soundController->playStop();
    this->lightController->flash(10, .25);
}

void GameController::step() {
    this->soundController->playStep();
    this->lightController->flash(10, .1);
    this->automatonController->step();
}

void GameController::startEdit() {
    this->state = STATE_EDITING;
    this->lightController->breathe(240, 2.0);
}

void GameController::stopEdit() {
    this->state = STATE_SUSPENDED;
    this->soundController->playStopEdit();
    this->lightController->flash(180, .25);
}

bool GameController::isWaiting() {
    return this->state == STATE_SUSPENDED;
}

bool GameController::isEditing() {
    return this->state == STATE_EDITING;
}

void GameController::lightOff() {
    this->lightController->off();
}

void GameController::update() {
    this->automatonController->update();
}