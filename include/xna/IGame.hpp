#pragma once
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <SDL2/SDL.h>

namespace xna {

    class IGame {
        public:

        ~IGame() {}
        virtual int GetKey(int key) {}
        virtual int SdlVersion() {}
        virtual void SdlVersion(int version) {}
        virtual SDL_Window* Window() {}
        virtual int Width() {}
        virtual int Height() {}
        virtual int MouseX() {}
        virtual int MouseY() {}
        virtual int MouseDown() {}
        virtual double Delta() {}
        virtual int IsRunning() {}
        virtual void Start() {}
        virtual void Stop() {}
        virtual void FpsChanged(int fps) {}
        virtual void Quit() {}
        virtual void Run() {}
        virtual void RunLoop() {}
        virtual void HandleEvents() {}
        virtual void Tick() {}
        virtual void Draw() {}
        virtual void Initialize() {}
        virtual void LoadContent() {}
        virtual void Update() {}
        
    };
}
