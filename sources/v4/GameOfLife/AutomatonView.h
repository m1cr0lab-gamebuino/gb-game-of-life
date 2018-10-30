#ifndef GAME_OF_LIFE_AUTOMATON_VIEW_H_
#define GAME_OF_LIFE_AUTOMATON_VIEW_H_

#include "bootstrap.h"
#include "Automaton.h"

class AutomatonView
{
    private:

        static const Color PALETTE[];
        
        Automaton* model;

    public:

        AutomatonView(Automaton* model);
        void draw();
};

#endif