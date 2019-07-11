#pragma once
#include "Game.h"
#include "GameWindow.h"

namespace xna {

    class Game;
    class GameWindow;
    class GamePlatform {
        
    public:
        GamePlatform();
        GamePlatform(Game* game);
        ~GamePlatform();    

        static GamePlatform* PlatformCreate(Game*);

        Game* game;
        GameWindow* window;
    };
}