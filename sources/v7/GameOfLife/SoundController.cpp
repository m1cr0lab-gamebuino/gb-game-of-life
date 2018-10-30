#include "SoundController.h"

const Gamebuino_Meta::Sound_FX SoundController::SFX_START[] = {
        {Gamebuino_Meta::Sound_FX_Wave::SQUARE, 0, 128, 0, -80, 50, 5}
};

SoundController::SoundController() {

}

void SoundController::playStart() {
    gb.sound.fx(SFX_START);
}

void SoundController::playStop() {
    gb.sound.playTick();
}

void SoundController::playStep() {
    gb.sound.playTick();
}

void SoundController::playStopEdit() {
    gb.sound.playOK();
}