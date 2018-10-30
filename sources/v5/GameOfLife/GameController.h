#ifndef GAME_OF_LIFE_GAME_CONTROLLER_H_
#define GAME_OF_LIFE_GAME_CONTROLLER_H_

#include "bootstrap.h"
#include "AutomatonController.h"
#include "EditorController.h"
#include "UserController.h"

class GameController
{
    private:

        static const uint8_t STATE_SUSPENDED;
        static const uint8_t STATE_RUNNING;
        static const uint8_t STATE_EDITING;

        AutomatonController* automatonController;
        EditorController* editorController;
        UserController* userController;
        uint8_t state;

        void initAutomatonController();
        void initEditorController();
        void initUserController();

    public:

        GameController();
        void begin();
        void loop();
        void clear();
        void randomize();
        void start();
        void stop();
        void step();
        void startEdit();
        void stopEdit();
        bool isWaiting();
        bool isEditing();
        void update();
};

#endif