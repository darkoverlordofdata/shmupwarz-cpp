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
#include <unistd.h>
#include <map>
#include <string>
#include <iostream>
#include <ctime>
#include <sys/time.h>
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

/**
 * Based on Microsoft.Xna.Framework.Game
 */
namespace xna {

    #ifdef __EMSCRIPTEN__
    #include <functional>
    #include <emscripten.h>
    std::function<void()> loop;
    void main_loop(void* arg);
    #endif
    #define TicksPerMillisecond  10000.0
    #define MillisecondsPerTick 1.0 / (TicksPerMillisecond)

    #define TicksPerSecond TicksPerMillisecond * 1000.0   // 10,000,000
    #define SecondsPerTick  1.0 / (TicksPerSecond)         // 0.0001

    using namespace std;
    using namespace core;

    enum {
        DISPLAY_WIDTH  = 480,
        DISPLAY_HEIGHT = 320,
        UPDATE_INTERVAL = 1000/60,
        HERO_SPEED = 2
    };

    static inline uint64_t GetTicks() { 
        static struct timeval t { .tv_sec = 0, .tv_usec = 0 };     
        gettimeofday(&t, nullptr);

        uint64_t ts = t.tv_sec;
        uint64_t us = t.tv_usec;
        return ((ts * 1000000L) + us) * 10;
    }


    class GamePlatform;

    
    class Game : public IGame {
        friend class IGamePlatform;
        protected:
        IFactory* mPlatformFactory;
        IGamePlatform * Platform;
        SDL_Window* mWindow;
        private:
        string mTitle;
        int mWidth;
        int mHeight;
        int mMouseX;
        int mMouseY;
        int mMouseDown = 0;
        double mDelta;
        int mSdlVersion;
        int mFrameSkip;
        int mIsRunning;
        int mTicks;
        int mFps;
        bool mIsFixedTimeStep;
        bool mIsRunningSlowly;
        uint64_t mTargetElapsedTime;
        uint64_t mAccumulatedElapsedTime;
        uint64_t mMaxElapsedTime;
        uint64_t mTotalGameTime;
        uint64_t mElapsedGameTime;
        uint64_t mCurrentTime;
        long mPreviousTicks;
        int mUpdateFrameLag;
        bool mShouldExit;
        bool mSuppressDraw;
        map<int,int> mKeys;
        
        public:

        Game() { }

        /**
         * Creates new game
         */
        Game(IFactory* platform, string t, int width, int height) :
            mTitle(t), 
            mWidth(width), 
            mHeight(height), 
            mFrameSkip(0), 
            mIsRunning(0), 
            mPreviousTicks(0),
            mIsFixedTimeStep(true), 
            mShouldExit(false), 
            mSuppressDraw(false), 
            mMaxElapsedTime(500 * TicksPerMillisecond), 
            mTargetElapsedTime(166667),
            mAccumulatedElapsedTime(0),
            mPlatformFactory(platform) ,
            IGame() 
        {
            
            printf("mTargetElapsedTime - %d\n", mTargetElapsedTime);
            printf("mMaxElapsedTime - %d\n", mMaxElapsedTime);
            Platform = GamePlatform::PlatformCreate(this, platform);
            // Platform = platform->CreateGamePlatform(this);
            // Platform = new SDLGamePlatform(this);
        }

        ~Game() {
            Platform->Dispose();
            delete Platform;
            printf("In Game::dtor\n");
            Stop();
            // SDL_DestroyWindow(mWindow);
            // IMG_Quit();
            // SDL_Quit();
        }

        int GetKey(int key) override {
            if (key > 255) return 0;
            return mKeys[key];
        }

        int SdlVersion() override {
            return mSdlVersion;
        }

        // void SetSdlVersion(int version) override {
        void SdlVersion(int version) override {
            printf("Game::SdlVersion = %d\n", mSdlVersion);
            mSdlVersion = version;
        }

        SDL_Window* Window() override {
            return mWindow;
        }

        void SetWindow(SDL_Window* window) override {
            mWindow = window;
        }

        const char* Title() override {
            return mTitle.c_str();
        }

        int Width() override {
            return mWidth;
        }

        int Height() override {
            return mHeight;
        }
        
        int MouseX() override {
            return mMouseX;
        }
        
        int MouseY() override {
            return mMouseY;
        }
        
        int MouseDown() override {
            return mMouseDown;
        }
        
        double Delta() override {
            return mDelta;
        }
        
        int IsRunning() override {
            return mIsRunning;
        }

        void Start() override {
            mIsRunning = 1;
        }



        void Stop() override {
            printf("stop\n");
        }

        void FpsChanged(int fps) override {
            char szFps[ 128 ];
            sprintf(szFps, "%s: %d", mTitle.c_str(), mFps);
            SDL_SetWindowTitle(mWindow, szFps);
            mFps = fps;
        }

        void Quit() override {
            mIsRunning = 0;
        }


        void Run() override {
            Initialize();
            LoadContent();
            Start();
        #ifdef __EMSCRIPTEN__
            loop = [&] 
            {
        #else
            while (IsRunning())  {
        #endif
                RunLoop();
                if (GetKey(SDLK_ESCAPE)) Quit();
            }
        #ifdef __EMSCRIPTEN__
            ;
            emscripten_set_main_loop_arg(main_loop, this, 0, true);
        #endif
        }

        void RunLoop() override {
            HandleEvents();
            Tick();
        }
        void HandleEvents() override {
            SDL_Event event;
            while (SDL_PollEvent(&event) != 0)  {
                switch (event.type)  {
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


            while (true)
            {
                // Advance the accumulated elapsed time.
                long currentTicks = GetTicks() - mCurrentTime;
                mAccumulatedElapsedTime = mAccumulatedElapsedTime + currentTicks - mPreviousTicks;
                mPreviousTicks = (long)currentTicks;

                // If we're in the fixed timestep mode and not enough time has elapsed
                // to perform an update we sleep off the the remaining time to save battery
                // life and/or release CPU time to other threads and processes.
                if (mIsFixedTimeStep && mAccumulatedElapsedTime < mTargetElapsedTime)
                {
                    int sleepTime = (int)((mTargetElapsedTime - mAccumulatedElapsedTime) * MillisecondsPerTick );
                    if (sleepTime < 1) break;
                    // NOTE: While sleep can be inaccurate in general it is 
                    // accurate enough for frame limiting purposes if some
                    // fluctuation is an acceptable result.
                    // SDL_Delay(sleepTime);
                    usleep(sleepTime*1000);
                    // goto RetryTick;
                }
                else break;
            }
            // Do not allow any update to take longer than our maximum.
            if (mAccumulatedElapsedTime > mMaxElapsedTime)
                mAccumulatedElapsedTime = mMaxElapsedTime;

            if (mIsFixedTimeStep)
            {
                mElapsedGameTime = mTargetElapsedTime;
                auto stepCount = 0;

                // Perform as many full fixed length time steps as we can.
                while (mAccumulatedElapsedTime >= mTargetElapsedTime && !mShouldExit)
                {
                    mTotalGameTime += mTargetElapsedTime;
                    mAccumulatedElapsedTime -= mTargetElapsedTime;
                    ++stepCount;
                    mDelta = (double)mElapsedGameTime * SecondsPerTick;
                    Update();
                    // DoUpdate(&mGameTime);
                }
                //Every update after the first accumulates lag
                mUpdateFrameLag += max(0, stepCount - 1);
                //If we think we are running slowly, wait until the lag clears before resetting it
                if (mIsRunningSlowly)
                {
                    if (mUpdateFrameLag == 0)
                 
                        mIsRunningSlowly = false;
                }
                else if (mUpdateFrameLag >= 5)
                {
                    //If we lag more than 5 frames, start thinking we are running slowly
                    mIsRunningSlowly = true;
                }
                //Every time we just do one update and one draw, then we are not running slowly, so decrease the lag
                if (stepCount == 1 && mUpdateFrameLag > 0)
                    mUpdateFrameLag--;

                // Draw needs to know the total elapsed time
                // that occured for the fixed length updates.
                mElapsedGameTime = mTargetElapsedTime * stepCount;

            }
            else
            {
                // Perform a single variable length update.
                mElapsedGameTime = mAccumulatedElapsedTime;
                mTotalGameTime += mAccumulatedElapsedTime;
                mAccumulatedElapsedTime = 0; 

                // Update();
                DoUpdate();
            }

            // Draw unless the update suppressed it.
            if (mSuppressDraw)
                mSuppressDraw = false;
            else
            {
                // Draw();
                DoDraw();
            }

            if (mShouldExit) mIsRunning = false;
                // Platform.Exit();
            
        }

        void DoUpdate()  {
            Update();
        }
        void DoDraw()  {
            Draw();
        }
        virtual void Draw() override {}
        virtual void Initialize() override {}
        virtual void LoadContent() override {}
        virtual void Update() override {}
        
    };

    #ifdef __EMSCRIPTEN__
    void main_loop(void* arg) { 
        auto game = (Game*)arg;
        game->RunLoop();
    }
    #endif
}
