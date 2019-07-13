#include "xna/Game.h"
namespace xna {

    
    using namespace std::chrono;

    #ifdef __EMSCRIPTEN__
    #include <functional>
    #include <emscripten.h>
    std::function<void()> loop;
    void main_loop() { 
        auto game = (Game*)arg;
        game->runLoop();
    }
    #endif

    Game::Game() { }

    Game::Game(std::string t, int width, int height, SDL_Window* w)
        : mTitle(t), mWidth(width), mHeight(height), mWindow(w), mFrameSkip(0), mIsRunning(0) {
            Platform = GamePlatform::PlatformCreate(this);
        }

    Game::~Game() {
        Stop();
    }

    int Game::GetKey(int key) {
        if (key > 255) return 0;
        return mKeys[key];
    }

    int Game::SdlVersion() {
        return mSdlVersion;
    }

    void Game::SetSdlVersion(int version) {
        mSdlVersion = version;
    }

        // int Width;
        // int Height;
        // int MouseX;
        // int MouseY;
        // int MouseDown = 0;
        // double Delta;

    SDL_Window* Game::Window() {
        return mWindow;
    }

    int Game::Width() {
        return mWidth;
    }

    int Game::Height() {
        return mHeight;
    }
    
    int Game::MouseX() {
        return mMouseX;
    }
    
    int Game::MouseY() {
        return mMouseY;
    }
    
    int Game::MouseDown() {
        return mMouseDown;
    }
    
    double Game::Delta() {
        return mDelta;
    }
    
    int Game::IsRunning() {
        return mIsRunning;
    }

    void Game::Start() {
        mIsRunning = 1;
        auto num = high_resolution_clock::period::num;
        auto den = high_resolution_clock::period::den;
        mFactor = (double)num/(double)den;
        mMark1 = high_resolution_clock::now();
    }



    void Game::Stop() {
        printf("Game::stop\n");
    }

    void Game::FpsChanged(int fps) {
        char szFps[ 128 ];
        sprintf(szFps, "%s: %d", mTitle.c_str(), mFps);
        SDL_SetWindowTitle(mWindow, szFps);
        mFps = fps;
    }

    void Game::Quit() {
        mIsRunning = 0;
    }


    void Game::Run() {
        Init();
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

    void Game::RunLoop() {
        HandleEvents();
        Tick();
    }
    void Game::HandleEvents() {
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

    void Game::Tick() {
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
    void Game::Draw() {}
    void Game::Init() {}
    void Game::LoadContent() {}
    void Game::Update() {}
}
