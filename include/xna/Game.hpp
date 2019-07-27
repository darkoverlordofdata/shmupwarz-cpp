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
#include "IGame.hpp"
#include "IFactory.hpp"
#include "GamePlatform.hpp"
#include "Rectangle.hpp"
#include "Point.hpp"
#include "DisplayOrientation.hpp"
#include "../core/Core.hpp"

namespace xna {

    using namespace std::chrono;

    enum {
        DISPLAY_WIDTH  = 480,
        DISPLAY_HEIGHT = 320,
        UPDATE_INTERVAL = 1000/60,
        HERO_SPEED = 2
    };

    class GamePlatform;

    
    class Game : public IGame {
        friend class IGamePlatform;
        public:
        IGamePlatform * Platform;

        #ifdef __EMSCRIPTEN__
        #include <functional>
        #include <emscripten.h>
        std::function<void()> loop;
        void main_loop() { 
            auto game = (Game*)arg;
            game->runLoop();
        }
        #endif

        Game() { }

        /**
         * Creates new game
         */
        Game(IFactory* platform, std::string t, int width, int height, SDL_Window* w)
            : mTitle(t), mWidth(width), mHeight(height), mWindow(w), mFrameSkip(0), mIsRunning(0) {
                Platform = GamePlatform::PlatformCreate(this, platform);
            }

        ~Game() {
            Stop();
        }

        int GetKey(int key) {
            if (key > 255) return 0;
            return mKeys[key];
        }

        int SdlVersion() {
            return mSdlVersion;
        }

        // void SetSdlVersion(int version) {
        void SdlVersion(int version) {
            printf("Game::SdlVersion = %d\n", mSdlVersion);
            mSdlVersion = version;
        }

        SDL_Window* Window() {
            return mWindow;
        }

        int Width() {
            return mWidth;
        }

        int Height() {
            return mHeight;
        }
        
        int MouseX() {
            return mMouseX;
        }
        
        int MouseY() {
            return mMouseY;
        }
        
        int MouseDown() {
            return mMouseDown;
        }
        
        double Delta() {
            return mDelta;
        }
        
        int IsRunning() {
            return mIsRunning;
        }

        void Start() {
            mIsRunning = 1;
            auto num = high_resolution_clock::period::num;
            auto den = high_resolution_clock::period::den;
            mFactor = (double)num/(double)den;
            mMark1 = high_resolution_clock::now();
        }



        void Stop() {
            printf("stop\n");
        }

        void FpsChanged(int fps) {
            char szFps[ 128 ];
            sprintf(szFps, "%s: %d", mTitle.c_str(), mFps);
            SDL_SetWindowTitle(mWindow, szFps);
            mFps = fps;
        }

        void Quit() {
            mIsRunning = 0;
        }


        void Run() {
            Initialize();
            LoadContent();
            Start();
        #ifdef __EMSCRIPTEN__
            loop = [&] 
            {
        #else
            while (IsRunning()) {
        #endif
                RunLoop();
                if (GetKey(SDLK_ESCAPE)) Quit();
            }
        #ifdef __EMSCRIPTEN__
            ;
            emscripten_set_main_loop_arg(main_loop, this, 0, true);
        #endif
        }

        void RunLoop() {
            HandleEvents();
            Tick();
        }
        void HandleEvents() {
            SDL_Event event;
            while (SDL_PollEvent(&event) != 0) {
                switch (event.type) {
                    case SDL_QUIT:    
                        Quit();       
                        return;     
                        break;
                    case SDL_KEYDOWN: 
                        mKeys[event.key.keysym.sym] = 1;
                        if (event.key.keysym.sym == SDLK_ESCAPE) {
                            Quit();       
                            return;     
                        }
                        break;
                    case SDL_KEYUP:   
                        mKeys[ event.key.keysym.sym ] = 0;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        mMouseDown = 1;
                        break;
                    case SDL_MOUSEBUTTONUP:
                        mMouseDown = 0;
                        break;
                    case SDL_MOUSEMOTION:
                        mMouseX = event.motion.x;
                        mMouseY = event.motion.y;
                        break;
                }
            }
        }

        void Tick() {
            mMark2 = high_resolution_clock::now();
            mDelta += ((double) duration_cast<nanoseconds>(mMark2 - mMark1).count()) * mFactor;
            mTicks += 1;
            mMark1 = mMark2;
            if (mDelta >= 0.01667) {
                Update();
                Draw();
                // printf("%f -- %d\n", delta, ticks);
                mDelta = 0.0;
                mTicks = 0;
            }

        }
        virtual void Draw() {}
        virtual void Initialize() {}
        virtual void LoadContent() {}
        virtual void Update() {}
        
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
