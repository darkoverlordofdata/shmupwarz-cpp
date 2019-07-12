#include "xna/GamePlatform.h"
#include "xna/SDL/SDLGamePlatform.h"

namespace xna {

    GamePlatform::GamePlatform() { }
    GamePlatform::GamePlatform(GameBase* game) { 
        this->game = game;
    }

    GamePlatform::~GamePlatform() {
    }

    GamePlatform* GamePlatform::PlatformCreate(GameBase* game) {
        return new SDLGamePlatform(game);
    }

}