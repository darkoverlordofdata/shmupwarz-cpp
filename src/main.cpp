#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#include <iostream>
#ifdef __EMSCRIPTEN__
#include <functional>
#include <emscripten.h>
std::function<void()> loop;
void main_loop() { loop(); }
#else
#define GLEW_STATIC
#include <GL/glew.h>
#endif
#include "IGameSystems.hpp"
#include "Shmupwarz.hpp"
#include "GameSystems.hpp"

using namespace std::chrono;

namespace A {
    class DerivedA : public artemis::Component { 
      public:
        DerivedA() {
            std::cout << "A::DerivedA constructor\n"; 
        } 
    }; 
}
RegisterType(A::DerivedA);

namespace B { class DerivedB : public artemis::Component { public: DerivedB() { std::cout << "B::DerivedB constructor\n"; } }; }
RegisterType(B::DerivedB);

namespace C { class DerivedC : public artemis::Component { public: DerivedC() { std::cout << "C::DerivedC constructor\n"; } }; }
RegisterType(C::DerivedC);

namespace D { class DerivedD : public artemis::Component { public: DerivedD() { std::cout << "D::DerivedD constructor\n"; } }; }
RegisterType(D::DerivedD);

/**
 */
inline void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

static inline void checkSDLError(int line = -1)
{
#ifndef NDEBUG
	const char *error = SDL_GetError();
	if (*error != '\0')
	{
		printf("SDL Error: %s\n", error);
		if (line != -1)
			printf(" + line: %i\n", line);
		SDL_ClearError();
	}
#endif
}

// The Width of the screen
const GLuint SCREEN_WIDTH = 900;
// The height of the screen
const GLuint SCREEN_HEIGHT = 600;

auto TITLE = "Shmupwarz";

int main(int argc, char** argv){
    std::srand(std::time(0));    

    // artemis::utils::UUID guid;

    // for (auto i=0; i<10; i++)
    //     printf("guid = %s\n", guid.RandomUUID().c_str());

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO)) {
        logSDLError(std::cout, "Init SDL");
        return 0;
    }

    /* Request opengl 3.3 context.
     * SDL doesn't have the ability to choose which profile at this time of writing,
     * but it should default to the core profile */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
#ifdef __EMSCRIPTEN__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#endif

    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    auto window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    auto maincontext = SDL_GL_CreateContext(window);
    checkSDLError(__LINE__);

    #ifdef __EMSCRIPTEN__
    const auto img_flags = IMG_INIT_PNG;
    #else
    const auto img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
    #endif

    if (IMG_Init(img_flags) != img_flags) {
        logSDLError(std::cout, "Init image");
    }
    TTF_Init();
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        logSDLError(std::cout, "Init mixer");
    }

    #ifndef __EMSCRIPTEN__
    // Load OpenGL EntryPoints for desktop
    glewExperimental = GL_TRUE;
    glewInit();
    glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.
    #endif
    
    // OpenGL configuration
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /** 
     * All of the above code should be rolled up into Game
     */

    Shmupwarz game(TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, window);
    game.SetSystem(new GameSystems(&game));
    game.Run();

    SDL_DestroyWindow(window);
	IMG_Quit();
    SDL_Quit();
    printf("That's all folks!\n");
    return 0;
}

