#include "xna/SDL/SDLGamePlatform.h"
namespace xna {

    SDLGamePlatform::SDLGamePlatform() { }
    SDLGamePlatform::SDLGamePlatform(Game* game) :GamePlatform(game) {
        
        SDL_version sversion;
        SDL_GetVersion(&sversion);

        game->sdlVersion = 100 * sversion.major + 10 * sversion.minor + sversion.patch;
        if (game->sdlVersion <= 204) {
            printf("Please use SDL 2.0.5 or higher.\n");

        }
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO);
        SDL_DisableScreenSaver();

        window = new SDLGameWindow(game);
        

     }

    SDLGamePlatform::~SDLGamePlatform() {
    }

}