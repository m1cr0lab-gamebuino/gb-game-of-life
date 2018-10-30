/*
 * Game of Life
 * 
 * auteur  : Stéphane Calderoni
 * date    : 25 octobre 2018
 * version : 5
 * 
 * - Mise en place d'un contrôleur principal pour la gestion du jeu
 * - Ajout d'un contrôleur pour la gestion des événements utilisateur
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