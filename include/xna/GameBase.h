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
#include "GamePlatform.h"
#include "Rectangle.h"
#include "Point.h"
#include "DisplayOrientation.h"

namespace xna {

    enum {
        DISPLAY_WIDTH  = 480,
        DISPLAY_HEIGHT = 320,
        UPDATE_INTERVAL = 1000/60,
        HERO_SPEED = 2
    };

    class GamePlatform;
    
    class GameBase {
    friend class GamePlatform;
        
    public:
        GameBase();
        GameBase(std::string title, int width, int height, SDL_Window* window);
        ~GameBase();
        void FpsChanged(int fps);
        int GetKey(int key);
        void HandleEvents();
        int IsRunning();
        void Run();
        void RunLoop();
        void Start();
        void Stop();
        void Tick();
        void Quit();
        virtual void Draw() = 0;
        virtual void Init() = 0;
        virtual void LoadContent() = 0;
        virtual void Update() = 0;

        GamePlatform * Platform;
    
        int SdlVersion;
        int MouseX;
        int MouseY;
        int MouseDown = 0;
        int Width;
        int Height;
        double Delta;
        int Ticks;
        int Fps;
        double Factor;
        std::chrono::time_point<std::chrono::high_resolution_clock>  Mark1;
        std::chrono::time_point<std::chrono::high_resolution_clock>  Mark2;
        int Running;
        int FrameSkip;
        std::string Title;
        std::map<int,int> Keys;
        SDL_Window* Window;
        SDL_Renderer* Renderer;
        SDL_Texture* Image;

    };
}
