#pragma once
#include "../GamePlatform.h"
#include "SDLGameWindow.h"

namespace xna {

    class GameBase;
    class SDLGameWindow;
    class SDLGamePlatform : public GamePlatform {
    friend class GameBase;
        
    public:
        SDLGamePlatform();
        SDLGamePlatform(GameBase* game);
        ~SDLGamePlatform();

        GameBase* game;
        
    };
}