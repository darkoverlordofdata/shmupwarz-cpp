#pragma once
#include "../IFactory.hpp"
#include "SDLGamePlatform.hpp"

namespace xna {

    class Game;
    class GamePlatform;

    class SDLFactory : public IFactory {
        public:
        GamePlatform* CreateGamePlatform(Game* game) 
        {
            return new SDLGamePlatform(game);
        }
    };
}