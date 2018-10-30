#ifndef GAME_OF_LIFE_AUTOMATON_CONTROLLER_H_
#define GAME_OF_LIFE_AUTOMATON_CONTROLLER_H_

#include "Automaton.h"
#include "AutomatonView.h"

class AutomatonController
{
    private:

        Automaton* model;
        AutomatonView* view;

    public:

        AutomatonController(Automaton* model, AutomatonView* view);
        void begin();
        void spawn(size_t x, size_t y);
        void kill(size_t x, size_t y);
        void clear();
        void randomize();
        void addPattern(const uint8_t* pattern, uint8_t x, uint8_t y);
        void loop();
        void step();
        void update();
};

#endif