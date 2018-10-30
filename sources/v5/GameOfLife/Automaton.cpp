#include "Automaton.h"

Automaton::Automaton() {

}

uint8_t Automaton::getCell(size_t x, size_t y) {
    return this->grid[x][y];
}

void Automaton::spawn(size_t x, size_t y) {
    this->grid[x][y] = 2;
}

void Automaton::kill(size_t x, size_t y) {
    this->grid[x][y] = 0;
}

void Automaton::clear() {
    size_t x,y;
    size_t xsup = W+1; // borne supérieure de x
    size_t ysup = H+1; // borne supérieure de y
    for (y=1; y<ysup; y++) {
        for (x=1; x<xsup; x++) {
            this->grid[x][y] = 0;
        }
    }
}

void Automaton::randomize() {
    size_t x,y;
    size_t xsup = W+1; // borne supérieure de x
    size_t ysup = H+1; // borne supérieure de y
    for (y=1; y<ysup; y++) {
        for (x=1; x<xsup; x++) {
            this->grid[x][y] = random(0,2) == 0 ? random(1, 4) : 0;
        }
    }
}

uint8_t Automaton::duplicate(uint8_t g) {
    return (g << 4) | (g & 0xF);
}

uint8_t Automaton::neighbours(size_t x, size_t y) {
    uint8_t n = 0;
    size_t x1 = x-1;
    size_t x2 = x+1;
    size_t y1 = y-1;
    size_t y2 = y+1;

    if (this->grid[x1][y1] & 0xF0) { n++; }
    if (this->grid[x][y1]  & 0xF0) { n++; }
    if (this->grid[x2][y1] & 0xF0) { n++; }
    if (this->grid[x1][y]  & 0xF0) { n++; }
    if (this->grid[x2][y]  & 0xF0) { n++; }
    if (this->grid[x1][y2] & 0xF0) { n++; }
    if (this->grid[x][y2]  & 0xF0) { n++; }
    if (this->grid[x2][y2] & 0xF0) { n++; }
    
    return n;
}

void Automaton::bufferize() {
    size_t x,y;
    size_t w = W+1;
    size_t h = H+1;
    size_t xsup = W+2;
    size_t ysup = H+2;

    for (y=1; y<ysup; y++) {
        for (x=1; x<xsup; x++) {
            // recopie de la partie visible de la grille
            this->grid[x][y] = this->duplicate(grid[x][y]);
        }
        // recopie vers la frange de gauche
        this->grid[0][y] = this->duplicate(grid[W][y]);
        // recopie vers la frange de droite
        this->grid[w][y] = this->duplicate(grid[1][y]);
    }

    for (x=1; x<xsup; x++) {
        // recopie vers la frange du haut
        this->grid[x][0] = this->duplicate(grid[x][H]);
        // recopie vers la frange du bas
        this->grid[x][h] = this->duplicate(grid[x][1]);
    }

    // recopie des coins
    this->grid[0][0] = this->duplicate(grid[W][H]);
    this->grid[w][0] = this->duplicate(grid[1][H]);
    this->grid[0][h] = this->duplicate(grid[W][1]);
    this->grid[w][h] = this->duplicate(grid[1][1]);
}

void Automaton::applyRules() {
    uint8_t n,g,b;
    size_t x,y;
    size_t xsup = W+1;
    size_t ysup = H+1;

    for (y=1; y<ysup; y++) {
        for (x=1; x<xsup; x++) {
            n = this->neighbours(x,y);
            // l'état courant de la cellule
            g = this->grid[x][y] & 0xF;
            // l'état de la cellule à la génération précédente
            b = this->grid[x][y] & 0xF0;
            if (g == 0) { // si la cellule est morte
                if (n == 3) {
                    g = 1;
                }
            } else { // sinon c'est qu'elle est vivante
                if (n == 2 || n == 3) {
                    if (g != 15) {
                        g++;
                    }
                } else {
                    g = 0;
                }
            }
            // on n'oublie pas de conserver l'état de la cellule
            // à la génération précédente, puisque la grille n'a
            // pas encore été totalement parcourue !
            this->grid[x][y] = b | g;
        }
    }
}

void Automaton::step() {
    this->bufferize();
    this->applyRules();
}