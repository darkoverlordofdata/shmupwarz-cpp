#include "xna/GamePlatform.h"
#include "xna/SDL/SDLGamePlatform.h"

namespace xna {

    GamePlatform::GamePlatform() { }
    GamePlatform::GamePlatform(Game* game) { 
        mGame = game;
    }

    GamePlatform::~GamePlatform() {
    }

    GamePlatform* GamePlatform::PlatformCreate(Game* game) {
        
        return new SDLGamePlatform(game);
    }

}