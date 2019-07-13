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
    
    class Game {
    friend class GamePlatform;
        
    public:
        Game();
        Game(std::string title, int width, int height, SDL_Window* window);
        ~Game();
        void FpsChanged(int fps);
        int GetKey(int key);
        int SdlVersion();
        void SetSdlVersion(int);
        int MouseX();
        int MouseY();
        int MouseDown();
        int Width();
        int Height();
        double Delta();
        SDL_Window* Window();


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
    
    private:
        SDL_Window* mWindow;
        std::string mTitle;
        int mWidth;
        int mHeight;
        int mMouseX;
        int mMouseY;
        int mMouseDown;
        double mDelta;
        int mSdlVersion;
        int mFrameSkip;
        int mIsRunning;
        int mTicks;
        int mFps;
        double mFactor;
        std::map<int,int> mKeys;
        std::chrono::time_point<std::chrono::high_resolution_clock> mMark1;
        std::chrono::time_point<std::chrono::high_resolution_clock> mMark2;

    };
}
