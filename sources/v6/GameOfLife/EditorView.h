#ifndef GAME_OF_LIFE_EDITOR_VIEW_H_
#define GAME_OF_LIFE_EDITOR_VIEW_H_

#include "bootstrap.h"
#include "Editor.h"

class EditorView
{
    private:

        static const Color PALETTE[];
        static const uint8_t SHAPE[];

        Editor* model;
        uint8_t clock;
        void drawShape();

    public:

        EditorView(Editor* model);
        void draw();
};

#endif