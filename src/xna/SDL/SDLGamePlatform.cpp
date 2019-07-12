#include "xna/SDL/SDLGamePlatform.h"
namespace xna {

    SDLGamePlatform::SDLGamePlatform() { }
    SDLGamePlatform::SDLGamePlatform(GameBase* game) :GamePlatform(game) {
        
        SDL_version sversion;
        SDL_GetVersion(&sversion);

        game->SdlVersion = 100 * sversion.major + 10 * sversion.minor + sversion.patch;
        if (game->SdlVersion <= 204) {
            printf("Please use SDL 2.0.5 or higher.\n");

        }
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO);
        SDL_DisableScreenSaver();

        window = new SDLGameWindow(game);
        

     }

    SDLGamePlatform::~SDLGamePlatform() {
    }

}