#include "EditorView.h"

const Color EditorView::PALETTE[] = {
    WHITE,
    LIGHTBLUE
};

const uint8_t EditorView::SHAPE[] = {
    7, 7,
    0, 0, 2, 2, 2, 0, 0,
    0, 0, 0, 1, 0, 0, 0,
    2, 0, 0, 0, 0, 0, 2,
    2, 1, 0, 0, 0, 1, 2,
    2, 0, 0, 0, 0, 0, 2,
    0, 0, 0, 1, 0, 0, 0,
    0, 0, 2, 2, 2, 0, 0
};

EditorView::EditorView(Editor* model) : model(model), clock(0) {

}

void EditorView::draw() {
    if (this->clock % 4 < 2) {
        this->drawShape();
    }

    this->clock++;
}

void EditorView::drawShape() {
    uint8_t x = this->model->getX();
    uint8_t y = this->model->getY();
    uint8_t w = SHAPE[0];
    uint8_t h = SHAPE[1];
    uint8_t dx = 1 + w/2;
    uint8_t dy = 1 + h/2;
    int8_t u,v;
    uint8_t c;
    size_t i,j;
    for (i=0; i<w; i++) {
        for (j=0; j<h; j++) {
            c = SHAPE[2+j+i*w];
            if (c) {
                u = x + j - dx;
                v = y + i - dy;

                if (u < 0) { u += W; }
                if (u > W) { u -= W; }
                if (v < 0) { v += H; }
                if (v > H) { v -= H; }

                gb.display.setColor(PALETTE[c-1]);
                gb.display.drawPixel(u, v);
            }
        }
    }
}