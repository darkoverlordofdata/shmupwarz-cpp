#pragma once
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <SDL2/SDL.h>

namespace xna {


    class IGame {
        public:

        ~IGame() {}
        virtual int GetKey(int key) = 0;
        virtual int SdlVersion() = 0;
        virtual void SdlVersion(int version) = 0;
        virtual SDL_Window* Window() = 0;
        virtual void SetWindow(SDL_Window* window) = 0;
        virtual const char* Title() = 0;
        virtual int Width() = 0;
        virtual int Height() = 0;
        virtual int MouseX() = 0;
        virtual int MouseY() = 0;
        virtual int MouseDown() = 0;
        virtual double Delta() = 0;
        virtual int IsRunning() = 0;
        virtual void Start() = 0;
        virtual void Stop() = 0;
        virtual void FpsChanged(int fps) = 0;
        virtual void Quit() = 0;
        virtual void Run() = 0;
        virtual void RunLoop() = 0;
        virtual void HandleEvents() = 0;
        virtual void Tick() = 0;
        virtual void Draw() = 0;
        virtual void Initialize() = 0;
        virtual void LoadContent() = 0;
        virtual void Update() = 0;
        
    };
}
