#include "GameController.h"

const uint8_t GameController::STATE_SUSPENDED = 0;
const uint8_t GameController::STATE_RUNNING   = 1;
const uint8_t GameController::STATE_EDITING   = 2;

GameController::GameController() : state(STATE_RUNNING) {
    this->initAutomatonController();
    this->initEditorController();
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

void GameController::initUserController() {
    this->userController = new UserController(this);
}

void GameController::begin() {
    this->automatonController->begin();
    this->editorController->begin();
    this->userController->begin();
}

void GameController::loop() {
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

void GameController::start() {
    this->state = STATE_RUNNING;
}

void GameController::stop() {
    this->state = STATE_SUSPENDED;
}

void GameController::step() {
    this->automatonController->step();
}

void GameController::startEdit() {
    this->state = STATE_EDITING;
}

void GameController::stopEdit() {
    this->state = STATE_SUSPENDED;
}

bool GameController::isWaiting() {
    return this->state == STATE_SUSPENDED;
}

bool GameController::isEditing() {
    return this->state == STATE_EDITING;
}

void GameController::update() {
    this->automatonController->update();
}