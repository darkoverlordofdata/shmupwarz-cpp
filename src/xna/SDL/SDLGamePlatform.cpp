#include "xna/SDL/SDLGamePlatform.h"
namespace xna {

    SDLGamePlatform::SDLGamePlatform() { }
    SDLGamePlatform::SDLGamePlatform(Game* game) :GamePlatform(game) {
        
        printf("1\n");
        SDL_version sversion;
        SDL_GetVersion(&sversion);
        int version = 100 * sversion.major + 10 * sversion.minor + sversion.patch;
        game->SetSdlVersion(version);
        if (version <= 204) {
            printf("Please use SDL 2.0.5 or higher.\n");

        }
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO);
        SDL_DisableScreenSaver();

        mWindow = new SDLGameWindow(game);
        

     }

    SDLGamePlatform::~SDLGamePlatform() {
    }

}