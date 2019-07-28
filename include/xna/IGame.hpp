#pragma once
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <SDL2/SDL.h>

namespace xna {

    class IGame {
        public:


        IGame() {
            printf("In IGame::ctor\n");
        }
        // ~IGame() {
        //     printf("In IGame::dtor\n");

        // }

        int GetKey(int key) {}
        int SdlVersion() {}
        void SdlVersion(int version) {}
        SDL_Window* Window() {}
        int Width() {}
        int Height() {}
        int MouseX() {}
        int MouseY() {}
        int MouseDown() {}
        double Delta() {}
        int IsRunning() {}
        void Start() {}
        void Stop() {}
        void FpsChanged(int fps) {}
        void Quit() {}
        void Run() {}
        void RunLoop() {}
        void HandleEvents() {}
        void Tick() {}
        void Draw() {}
        void Initialize() {}
        void LoadContent() {}
        void Update() {}
        // virtual void Draw() {}
        // virtual void Initialize() {}
        // virtual void LoadContent() {}
        // virtual void Update() {}
        
    };
}
