/*
 * Game of Life
 * 
 * auteur  : Stéphane Calderoni
 * date    : 20 octobre 2018
 * version : 3
 * 
 * Programmation Orientée Objet
 */

#include "bootstrap.h"
#include "Automaton.h"

Automaton* automaton;

void setup() {
    gb.begin();

    automaton = new Automaton();
    automaton->randomize();
}

void loop() {
    
    while (!gb.update());

    if (gb.buttons.pressed(BUTTON_A)) {
        automaton->randomize();
    }

    automaton->step();
    automaton->draw();
}