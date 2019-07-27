#pragma once
#include "IGame.hpp"
#include "IGamePlatform.hpp"

namespace xna {

    class Game;
    class GamePlatform;

    class IFactory {
        public:
        IGamePlatform* CreateGamePlatform(IGame* game) {};
    };
}