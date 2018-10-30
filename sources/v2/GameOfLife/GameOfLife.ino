/*
 * Game of Life
 * 
 * auteur  : Stéphane Calderoni
 * date    : 20 octobre 2018
 * version : 2
 * 
 * Optimisation de l'occupation mémoire et de la vitesse d'exécution
 */

#include <Gamebuino-Meta.h>

#define W 80
#define H 64

const Color PALETTE[] = {BLACK, GREEN, LIGHTGREEN, WHITE, YELLOW, BEIGE, BROWN, ORANGE, RED, PINK, PURPLE, DARKBLUE, BLUE, LIGHTBLUE, GRAY, DARKGRAY};

uint8_t grid[W+2][H+2];

void setup() {
    gb.begin();
    randomize();
    draw();
}

void loop() {
    while (!gb.update());

    if (gb.buttons.pressed(BUTTON_A)) {
        randomize();
    }

    step();
}

void step() {
    bufferize();
    applyRules();
    draw();
}

void randomize() {
    size_t x,y;
    size_t xsup = W+1; // borne supérieure de x
    size_t ysup = H+1; // borne supérieure de y
    for (y=1; y<ysup; y++) {
        for (x=1; x<xsup; x++) {
            grid[x][y] = random(0,2) == 0 ? random(1, 4) : 0;
        }
    }
}

uint8_t duplicate(uint8_t g) {
    return (g << 4) | (g & 0xF);
}

void bufferize() {
    size_t x,y;
    size_t w = W+1;
    size_t h = H+1;
    size_t xsup = W+2;
    size_t ysup = H+2;

    for (y=1; y<ysup; y++) {
        for (x=1; x<xsup; x++) {
            // recopie de la partie visible de la grille
            grid[x][y] = duplicate(grid[x][y]);
        }
        // recopie vers la frange de gauche
        grid[0][y] = duplicate(grid[W][y]);
        // recopie vers la frange de droite
        grid[w][y] = duplicate(grid[1][y]);
    }

    for (x=1; x<xsup; x++) {
        // recopie vers la frange du haut
        grid[x][0] = duplicate(grid[x][H]);
        // recopie vers la frange du bas
        grid[x][h] = duplicate(grid[x][1]);
    }

    // recopie des coins
    grid[0][0] = duplicate(grid[W][H]);
    grid[w][0] = duplicate(grid[1][H]);
    grid[0][h] = duplicate(grid[W][1]);
    grid[w][h] = duplicate(grid[1][1]);
}

uint8_t neighbours(size_t x, size_t y) {
    uint8_t n = 0;
    size_t x1 = x-1;
    size_t x2 = x+1;
    size_t y1 = y-1;
    size_t y2 = y+1;

    if (grid[x1][y1] & 0xF0) { n++; }
    if (grid[x][y1]  & 0xF0) { n++; }
    if (grid[x2][y1] & 0xF0) { n++; }
    if (grid[x1][y]  & 0xF0) { n++; }
    if (grid[x2][y]  & 0xF0) { n++; }
    if (grid[x1][y2] & 0xF0) { n++; }
    if (grid[x][y2]  & 0xF0) { n++; }
    if (grid[x2][y2] & 0xF0) { n++; }
    
    return n;
}

void applyRules() {
    uint8_t n,g,b;
    size_t x,y;
    size_t xsup = W+1;
    size_t ysup = H+1;

    for (y=1; y<ysup; y++) {
        for (x=1; x<xsup; x++) {
            n = neighbours(x,y);
            // l'état courant de la cellule
            g = grid[x][y] & 0xF;
            // l'état de la cellule à la génération précédente
            b = grid[x][y] & 0xF0;
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
            grid[x][y] = b | g;
        }
    }
}

void draw() {
    uint8_t i,j,y,g;
    gb.display.clear();
    for (i=0; i<H; i++) {
        y = i+1;
        for (j=0; j<W; j++) {
            g = grid[j+1][y] & 0xF;
            if (g) {
                gb.display.setColor(PALETTE[g]);
                gb.display.drawPixel(j,i);
            }
        }
    }
}