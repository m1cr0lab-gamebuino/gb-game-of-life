/*
 * Game of Life
 * 
 * auteur  : Stéphane Calderoni
 * date    : 20 octobre 2018
 * version : 1
 */

#include <Gamebuino-Meta.h>

#define W 80
#define H 64

const Color PALETTE[] = {BLACK, GREEN, LIGHTGREEN, WHITE, YELLOW, BEIGE, BROWN, ORANGE, RED, PINK, PURPLE, DARKBLUE, BLUE, LIGHTBLUE, GRAY, DARKGRAY};

uint8_t grid[W][H];
uint8_t buffer[W][H];

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
    for (y=0; y<H; y++) {
        for (x=0; x<W; x++) {
            grid[x][y] = random(0,2) == 0 ? random(1, 4) : 0;
        }
    }
}

void bufferize() {
    size_t x,y;
    for (y=0; y<H; y++) {
        for (x=0; x<W; x++) {
            buffer[x][y] = grid[x][y];
        }
    }
}

uint8_t neighbours(size_t x, size_t y) {
    uint8_t n = 0;
    int8_t i,j,u,v;
    for (i=-1; i<2; i++) {
        for (j=-1; j<2; j++) {
            if (i != 0 || j != 0) {
                u = x + j;
                v = y + i;

                if (u == -1) {
                    u = W - 1;
                } else if (u == W) {
                    u = 0;
                }

                if (v == -1) {
                    v = H - 1;
                } else if (v == H) {
                    v = 0;
                }

                if (buffer[u][v]) {
                    n++;
                }
            }
        }
    }
    return n;
}

void applyRules() {
    uint8_t n;
    size_t x,y;
    for (y=0; y<H; y++) {
        for (x=0; x<W; x++) {
            n = neighbours(x,y);
            if (grid[x][y] == 0) { // si la cellule est morte
                if (n == 3) {
                    grid[x][y] = 1;
                }
            } else { // sinon c'est qu'elle est vivante
                if (n == 2 || n == 3) {
                    if (grid[x][y] != 15) {
                        grid[x][y]++;
                    }
                } else {
                    grid[x][y] = 0;
                }
            }
        }
    }
}

void draw() {
    uint8_t x,y;
    gb.display.clear();
    for (y=0; y<H; y++) {
        for (x=0; x<W; x++) {
            if (grid[x][y]) {
                gb.display.setColor(PALETTE[grid[x][y]]);
                gb.display.drawPixel(x,y);
            }
        }
    }
}