#pragma once
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <list>
#include <vector>
#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <ctime>
#include <chrono>
#include <list>
#include <algorithm>
#include <random>
#include <chrono>

namespace xna {

    enum {
        DISPLAY_WIDTH  = 480,
        DISPLAY_HEIGHT = 320,
        UPDATE_INTERVAL = 1000/60,
        HERO_SPEED = 2
    };

    class Game {
        
    public:
        Game();
        Game(std::string title, int width, int height, SDL_Window* window);
        ~Game();
        virtual void start();
        void run();
        void runLoop();
        void tick();
        void stop();
        void handleEvents();
        void fpsChanged(int fps);
        void quit();
        int isRunning();
        int getKey(int key);
        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void init() = 0;

    
        int mouseX;
        int mouseY;
        int mouseDown = 0;
        int width;
        int height;
        double delta;
        int ticks;
        int fps;
        double factor;
        std::chrono::time_point<std::chrono::high_resolution_clock>  mark1;
        std::chrono::time_point<std::chrono::high_resolution_clock>  mark2;
        int running;
        int frameSkip;
        std::string title;
        std::map<int,int> keys;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* image;

    };
}
