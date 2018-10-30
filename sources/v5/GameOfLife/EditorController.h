#ifndef GAME_OF_LIFE_EDITOR_CONTROLLER_H_
#define GAME_OF_LIFE_EDITOR_CONTROLLER_H_

#include "Editor.h"
#include "EditorView.h"
#include "AutomatonController.h"

class EditorController
{
    private:

        Editor* model;
        EditorView* view;
        AutomatonController* automatonController;

    public:

        EditorController(Editor* model, EditorView* view, AutomatonController* automatonController);
        void begin();
        void loop();
        void update();
};

#endif