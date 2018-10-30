#ifndef GAME_OF_LIFE_USER_CONTROLLER_H_
#define GAME_OF_LIFE_USER_CONTROLLER_H_

// Forward declaration
class GameController;

class UserController
{
    private:

        static const char* MAIN_MENU[];
        
        GameController* gameController;

        void checkButtons();
        void openMainMenu();

    public:

        UserController(GameController* gameController);
        void begin();
        void loop();
};

#endif