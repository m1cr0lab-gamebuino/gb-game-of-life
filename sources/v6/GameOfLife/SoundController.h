#ifndef GAME_OF_LIFE_SOUND_CONTROLLER_H_
#define GAME_OF_LIFE_SOUND_CONTROLLER_H_

#include "bootstrap.h"

class SoundController
{
    private:

        static const Gamebuino_Meta::Sound_FX SFX_START[];

    public:

        SoundController();

        void playStart();
        void playStop();
        void playStep();
        void playStopEdit();
};

#endif