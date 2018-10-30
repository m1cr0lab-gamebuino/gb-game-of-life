#ifndef GAME_OF_LIFE_USER_CONTROLLER_H_
#define GAME_OF_LIFE_USER_CONTROLLER_H_

#include "Pattern.h"

// Forward declaration
class GameController;

class UserController
{
    private:

        static const char* MAIN_MENU[];
        static const char* PATTERN_MENU[];
        
        GameController* gameController;

        void checkButtons();
        void openMainMenu();
        void openPatternMenu();

    public:

        UserController(GameController* gameController);
        void begin();
        void loop();
};

#endif