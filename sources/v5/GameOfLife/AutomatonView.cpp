#include "AutomatonView.h"

const Color AutomatonView::PALETTE[] = {BLACK, GREEN, LIGHTGREEN, WHITE, YELLOW, BEIGE, BROWN, ORANGE, RED, PINK, PURPLE, DARKBLUE, BLUE, LIGHTBLUE, GRAY, DARKGRAY};

AutomatonView::AutomatonView(Automaton* model) : model(model) {

};

void AutomatonView::draw() {
    uint8_t i,j,y,g;
    gb.display.clear();
    for (i=0; i<H; i++) {
        y = i+1;
        for (j=0; j<W; j++) {
            g = this->model->getCell(j+1, y) & 0xF;
            if (g) {
                gb.display.setColor(PALETTE[g]);
                gb.display.drawPixel(j,i);
            }
        }
    }
}