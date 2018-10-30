#ifndef GAME_OF_LIFE_AUTOMATON_H_
#define GAME_OF_LIFE_AUTOMATON_H_

#include "bootstrap.h"

class Automaton
{
    private:

        uint8_t grid[W+2][H+2];

        uint8_t duplicate(uint8_t g);
        uint8_t neighbours(size_t x, size_t y);
        void bufferize();
        void applyRules();

    public:

        Automaton();
        void randomize();
        void step();
        void draw();
};

#endif