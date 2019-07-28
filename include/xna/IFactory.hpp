#pragma once
#include "IGame.hpp"
#include "IGamePlatform.hpp"

namespace xna {

    class IGame;
    class IGamePlatform;

    class IFactory {
        public:
        ~IFactory() {}
        virtual IGamePlatform* CreateGamePlatform(IGame* game) = 0;
    };
}