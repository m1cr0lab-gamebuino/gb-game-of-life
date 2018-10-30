/*
 * Game of Life
 * 
 * auteur  : Stéphane Calderoni
 * date    : 21 octobre 2018
 * version : 4
 * 
 * Architecture Model View Controller
 */

#include "bootstrap.h"
#include "Automaton.h"
#include "AutomatonView.h"
#include "AutomatonController.h"

Automaton* automaton;
AutomatonView* automatonView;
AutomatonController* automatonController;

void setup() {
    gb.begin();

    automaton = new Automaton();
    automatonView = new AutomatonView(automaton);
    automatonController = new AutomatonController(automaton, automatonView);
    
    automatonController->begin();
}

void loop() {
    
    while (!gb.update());

    if (gb.buttons.pressed(BUTTON_A)) {
        automatonController->randomize();
    }

    automatonController->loop();
}