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

    #ifdef __EMSCRIPTEN__
    #include <functional>
    #include <emscripten.h>
    std::function<void()> loop;
    void main_loop(void* arg);
    #endif
    using namespace std;
    using namespace std::chrono;
    using namespace core;

    enum {
        DISPLAY_WIDTH  = 480,
        DISPLAY_HEIGHT = 320,
        UPDATE_INTERVAL = 1000/60,
        HERO_SPEED = 2
    };

    class GamePlatform;

    
    class Game : public IGame {
        friend class IGamePlatform;
        protected:
        IFactory* PlatformFactory;
        IGamePlatform * Platform;
        private:
        SDL_Window* mWindow;
        std::string mTitle;
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
        TimeSpan mTargetElapsedTime;
        TimeSpan mAccumulatedElapsedTime;// = TimeSpan.Zero;
        TimeSpan mMaxElapsedTime;
        GameTime mGameTime;
        // GameTime _gameTime = new GameTime();
        // public GameTime gameTime { get; construct; }
        Stopwatch* mGameTimer;
        long mPreviousTicks;
        int mUpdateFrameLag;
        bool mShouldExit;
        bool mSuppressDraw;

        float mLerp;
        double mFactor;
        std::map<int,int> mKeys;
        
        std::chrono::time_point<std::chrono::high_resolution_clock> mMark1;
        std::chrono::time_point<std::chrono::high_resolution_clock> mMark2;

        public:

        Game() { }

        /**
         * Creates new game
         */
        Game(IFactory* platform, std::string t, int width, int height, SDL_Window* w)
            : mTitle(t), mWidth(width), mHeight(height), mWindow(w), mFrameSkip(0), 
                mIsRunning(0), mPreviousTicks(0),
                mIsFixedTimeStep(true), mShouldExit(false), mSuppressDraw(false), 
                mMaxElapsedTime(TimeSpan::FromMilliseconds(500)), 
                mTargetElapsedTime(TimeSpan::FromTicks(166667)),
                mAccumulatedElapsedTime(TimeSpan::FromTicks(0)),
                mGameTimer(Stopwatch::StartNew()),
                IGame() 
        {
            
            printf("mTargetElapsedTime - %d\n", mTargetElapsedTime.mTicks);
            printf("mMaxElapsedTime - %d\n", mMaxElapsedTime.mTicks);
            PlatformFactory = platform ;
            Platform = GamePlatform::PlatformCreate(this, platform);
        }

        ~Game() {
            printf("In Game::dtor\n");
            Stop();
        }

        // void SetFactory(IFactory* platform)
        // {
        //     auto me = this;
        //     printf("In SetFactory\n");
        //     if (me == nullptr) printf("this is null in Game ctor\n");
        //     Platform = GamePlatform::PlatformCreate(me, platform);
        // }

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
            return 0.01667;
            // return mDelta / mLerp;
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


            while (true)
            {
                // Advance the accumulated elapsed time.
                auto currentTicks = mGameTimer->ElapsedTicks();
                mAccumulatedElapsedTime.Plus(TimeSpan::FromTicks(currentTicks - mPreviousTicks));
                mPreviousTicks = (long)currentTicks;

                // If we're in the fixed timestep mode and not enough time has elapsed
                // to perform an update we sleep off the the remaining time to save battery
                // life and/or release CPU time to other threads and processes.

                if (mIsFixedTimeStep && mAccumulatedElapsedTime.mTicks < mTargetElapsedTime.mTicks)
                {
                    auto sleepTime = (int)(mTargetElapsedTime - mAccumulatedElapsedTime).TotalMilliseconds();
                    if (sleepTime < 1) break;
                    // NOTE: While sleep can be inaccurate in general it is 
                    // accurate enough for frame limiting purposes if some
                    // fluctuation is an acceptable result.
                    // GLib.Thread.usleep(sleepTime*1000);
                    SDL_Delay(sleepTime);
                    // System.Threading.Thread.Sleep(sleepTime);
                    // goto RetryTick;
                    break;
                }
                else break;
            }
            // Do not allow any update to take longer than our maximum.
            // if (mAccumulatedElapsedTime > mMaxElapsedTime)
            //     mAccumulatedElapsedTime = mMaxElapsedTime;
            Update();

            // printf("(%d) %d %d\n", mAccumulatedElapsedTime.mTicks - mPreviousTicks, mAccumulatedElapsedTime.mTicks, mPreviousTicks);
            if (mIsFixedTimeStep)
            {
                mGameTime.ElapsedGameTime = mTargetElapsedTime;
                auto stepCount = 0;

                // Perform as many full fixed length time steps as we can.
                while (mAccumulatedElapsedTime >= mTargetElapsedTime && !mShouldExit)
                {
                    // gameTime.TotalGameTime.Plus(_accumulatedElapsedTime);
                    // _accumulatedElapsedTime.Minus(TargetElapsedTime);

                    // CRITICAL CODE FAILS UNLESS I DO THIS
                    int elapsed = (int)mAccumulatedElapsedTime.mTicks;
                    int target = (int)mTargetElapsedTime.mTicks;
                    mGameTime.TotalGameTime.mTicks += elapsed;
                    mAccumulatedElapsedTime.mTicks = elapsed - target;

                    ++stepCount;

                    Update();
                    // DoUpdate(&mGameTime);
                }
                //Every update after the first accumulates lag
                mUpdateFrameLag += max(0, stepCount - 1);
                //If we think we are running slowly, wait until the lag clears before resetting it
                if (mGameTime.IsRunningSlowly)
                {
                    if (mUpdateFrameLag == 0)
                        mGameTime.IsRunningSlowly = false;
                }
                else if (mUpdateFrameLag >= 5)
                {
                    //If we lag more than 5 frames, start thinking we are running slowly
                    mGameTime.IsRunningSlowly = true;
                }
                //Every time we just do one update and one draw, then we are not running slowly, so decrease the lag
                if (stepCount == 1 && mUpdateFrameLag > 0)
                    mUpdateFrameLag--;

                // Draw needs to know the total elapsed time
                // that occured for the fixed length updates.
                mGameTime.ElapsedGameTime = TimeSpan::FromTicks(mTargetElapsedTime.mTicks * stepCount);

            }
            else
            {
                // Perform a single variable length update.
                mGameTime.ElapsedGameTime = mAccumulatedElapsedTime;
                mGameTime.TotalGameTime.Plus(mAccumulatedElapsedTime);
                mAccumulatedElapsedTime = TimeSpan(0);

                Update();
                // DoUpdate(&mGameTime);
            }

            // Draw unless the update suppressed it.
            if (mSuppressDraw)
                mSuppressDraw = false;
            else
            {
                Draw();
                // DoDraw(&mGameTime);
            }

            if (mShouldExit) mIsRunning = false;
                // Platform.Exit();
            
            return;

            // mMark2 = high_resolution_clock::now();
            // mDelta += ((double) duration_cast<nanoseconds>(mMark2 - mMark1).count()) * mFactor;
            // mMark1 = mMark2;
            // mTicks += 1;
            // while (mDelta >= 0.01667) {
            //     mDelta -= 0.01667;
            //     mLerp = mDelta / 0.01667;
            //     mTicks = 0;
            //     Update();
            // }
            // Draw();
        }

        void DoUpdate(GameTime* g) {
            Update();
        }
        void DoDraw(GameTime* g) {
            Draw();
        }
        virtual void Draw() {}
        virtual void Initialize() {}
        virtual void LoadContent() {}
        virtual void Update() {}
        
    };

    #ifdef __EMSCRIPTEN__
    void main_loop(void* arg) { 
        auto game = (Game*)arg;
        game->RunLoop();
    }
    #endif
}
