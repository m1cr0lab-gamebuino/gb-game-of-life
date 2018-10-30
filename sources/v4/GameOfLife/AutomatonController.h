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
        void randomize();
        void loop();
};

#endif