#pragma once
#include "../IFactory.hpp"
#include "../IGame.hpp"

#include "SDLGamePlatform.hpp"

namespace xna {

    class IGame;
    class IGamePlatform;
    class SDLGamePlatform;

    class SDLFactory : public IFactory {
        public:
        SDLFactory() {
            printf("Create SDLFactory\n");
        }
        IGamePlatform* CreateGamePlatform(IGame* game) override
        {
            printf("In SDLFactory::CreateGamePlatform\n");
            return new SDLGamePlatform(game);
            // return nullptr;
        }
    };
}