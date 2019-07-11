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
        : title(t), width(width), height(height), window(w), frameSkip(0), running(0) {
            Platform = GamePlatform::PlatformCreate(this);
        }

    Game::~Game() {
        stop();
    }

    int Game::getKey(int key) {
        if (key > 255) return 0;
        return keys[key];
    }
    int Game::isRunning() {
        return running;
    }

    void Game::start() {
        running = 1;
        auto num = high_resolution_clock::period::num;
        auto den = high_resolution_clock::period::den;
        factor = (double)num/(double)den;
        mark1 = high_resolution_clock::now();
    }



    void Game::stop() {
        printf("Game::stop\n");
    }

    void Game::fpsChanged(int fps) {
        char szFps[ 128 ];
        sprintf(szFps, "%s: %d", title.c_str(), fps);
        SDL_SetWindowTitle(window, szFps);
        this->fps = fps;
    }

    void Game::quit() {
        running = 0;
    }


    void Game::run() {
        init();
        loadContent();
        start();
    #ifdef __EMSCRIPTEN__
        loop = [&] 
        {
    #else
        while (isRunning()) {
    #endif
            runLoop();
            if (getKey(SDLK_ESCAPE)) quit();
        }
    #ifdef __EMSCRIPTEN__
        ;
        emscripten_set_main_loop_arg(main_loop, this, 0, true);
    #endif
    }

    void Game::runLoop() {
        handleEvents();
        tick();
    }
    void Game::handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:    
                    quit();       
                    return;     
                    break;
                case SDL_KEYDOWN: 
                    keys[event.key.keysym.sym] = 1;
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        quit();       
                        return;     
                    }
                    break;
                case SDL_KEYUP:   
                    keys[ event.key.keysym.sym ] = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouseDown = 1;
                    break;
                case SDL_MOUSEBUTTONUP:
                    mouseDown = 0;
                    break;
                case SDL_MOUSEMOTION:
                    mouseX = event.motion.x;
                    mouseY = event.motion.y;
                    break;
            }
        }
    }

    void Game::tick() {
        mark2 = high_resolution_clock::now();
        delta += ((double) duration_cast<nanoseconds>(mark2 - mark1).count()) * factor;
        ticks += 1;
        mark1 = mark2;
        if (delta >= 0.01667) {
            update();
            draw();
            // printf("%f -- %d\n", delta, ticks);
            delta = 0.0;
            ticks = 0;
        }

    }
    void Game::draw() {}
    void Game::init() {}
    void Game::loadContent() {}
    void Game::update() {}
}
