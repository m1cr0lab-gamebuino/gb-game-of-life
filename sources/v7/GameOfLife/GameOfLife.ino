/*
 * Game of Life
 * 
 * auteur  : Stéphane Calderoni
 * date    : 28 octobre 2018
 * version : 6
 * 
 * - Ajout d'un gestionnaire MVC d'activation des LEDs
 * - Ajout d'un contrôleur de gestion du son
 */

#include "bootstrap.h"
#include "GameController.h"

GameController* gameController;

void setup() {
    gb.begin();

    gameController = new GameController();
    gameController->begin();
    
}

void loop() {
    while (!gb.update());
    
    gameController->loop();
}