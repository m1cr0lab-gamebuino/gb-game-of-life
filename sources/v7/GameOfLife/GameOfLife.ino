/*
 * Game of Life
 * 
 * auteur  : Stéphane Calderoni
 * date    : 28 octobre 2018
 * version : 7
 * 
 * - Ajout de la gestion des motifs remarquables du Jeu de la Vie
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
