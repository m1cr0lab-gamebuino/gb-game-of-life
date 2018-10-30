#ifndef GAME_OF_LIFE_EDITOR_H_
#define GAME_OF_LIFE_EDITOR_H_

#include "bootstrap.h"

class Editor
{
    private:

        uint8_t x, y;

    public:

        Editor(uint8_t x, uint8_t y);
        uint8_t getX();
        uint8_t getY();
        void up();
        void down();
        void left();
        void right();
};

#endif