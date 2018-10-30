#include "Editor.h"

Editor::Editor(uint8_t x, uint8_t y) : x(x), y(y) {

}

uint8_t Editor::getX() {
    return this->x;
}

uint8_t Editor::getY() {
    return this->y;
}

void Editor::up() {
    if (this->y == 0) {
        this->y = H;
    } else {
        this->y--;
    }
}

void Editor::down() {
    if (this->y == H) {
        this->y = 0;
    } else {
        this->y++;
    }
}

void Editor::left() {
    if (this->x == 0) {
        this->x = W;
    } else {
        this->x--;
    }
}

void Editor::right() {
    if (this->x == W) {
        this->x = 0;
    } else {
        this->x++;
    }
}