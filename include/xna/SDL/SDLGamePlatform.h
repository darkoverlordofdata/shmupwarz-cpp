#pragma once
#include "../GamePlatform.h"
#include "SDLGameWindow.h"

namespace xna {

    class Game;
    class SDLGameWindow;
    class SDLGamePlatform : public GamePlatform {
    friend class Game;
        
    public:
        SDLGamePlatform();
        SDLGamePlatform(Game* game);
        ~SDLGamePlatform();

    protected:
        Game* mGame;
        
    };
}