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

// void test();

int main(int argc, char** argv){

    Shmupwarz game("Shmupwarz", 900, 600);
    game.SetSystem(new GameSystems(&game));
    game.Run();

    printf("That's all folks!\n");
    return 0;
}

