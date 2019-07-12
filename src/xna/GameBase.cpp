#include "xna/GameBase.h"
namespace xna {

    
    using namespace std::chrono;

    #ifdef __EMSCRIPTEN__
    #include <functional>
    #include <emscripten.h>
    std::function<void()> loop;
    void main_loop() { 
        auto game = (GameBase*)arg;
        game->runLoop();
    }
    #endif

    GameBase::GameBase() { }

    GameBase::GameBase(std::string t, int width, int height, SDL_Window* w)
        : Title(t), Width(width), Height(height), Window(w), FrameSkip(0), Running(0) {
            Platform = GamePlatform::PlatformCreate(this);
        }

    GameBase::~GameBase() {
        Stop();
    }

    int GameBase::GetKey(int key) {
        if (key > 255) return 0;
        return Keys[key];
    }
    int GameBase::IsRunning() {
        return Running;
    }

    void GameBase::Start() {
        Running = 1;
        auto num = high_resolution_clock::period::num;
        auto den = high_resolution_clock::period::den;
        Factor = (double)num/(double)den;
        Mark1 = high_resolution_clock::now();
    }



    void GameBase::Stop() {
        printf("GameBase::stop\n");
    }

    void GameBase::FpsChanged(int fps) {
        char szFps[ 128 ];
        sprintf(szFps, "%s: %d", Title.c_str(), Fps);
        SDL_SetWindowTitle(Window, szFps);
        Fps = fps;
    }

    void GameBase::Quit() {
        Running = 0;
    }


    void GameBase::Run() {
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

    void GameBase::RunLoop() {
        HandleEvents();
        Tick();
    }
    void GameBase::HandleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:    
                    Quit();       
                    return;     
                    break;
                case SDL_KEYDOWN: 
                    Keys[event.key.keysym.sym] = 1;
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        Quit();       
                        return;     
                    }
                    break;
                case SDL_KEYUP:   
                    Keys[ event.key.keysym.sym ] = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    MouseDown = 1;
                    break;
                case SDL_MOUSEBUTTONUP:
                    MouseDown = 0;
                    break;
                case SDL_MOUSEMOTION:
                    MouseX = event.motion.x;
                    MouseY = event.motion.y;
                    break;
            }
        }
    }

    void GameBase::Tick() {
        Mark2 = high_resolution_clock::now();
        Delta += ((double) duration_cast<nanoseconds>(Mark2 - Mark1).count()) * Factor;
        Ticks += 1;
        Mark1 = Mark2;
        if (Delta >= 0.01667) {
            Update();
            Draw();
            // printf("%f -- %d\n", delta, ticks);
            Delta = 0.0;
            Ticks = 0;
        }

    }
    void GameBase::Draw() {}
    void GameBase::Init() {}
    void GameBase::LoadContent() {}
    void GameBase::Update() {}
}
