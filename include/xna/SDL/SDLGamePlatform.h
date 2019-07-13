#pragma once
#include "../GamePlatform.h"
#include "SDLGameWindow.h"

namespace xna {

    class Game;
    class SDLGameWindow;
    class SDLGamePlatform : public GamePlatform {
    friend class Game;
        
    public:
        SDLGamePlatform();
        SDLGamePlatform(Game* game);
        ~SDLGamePlatform();
        GameRunBehavior DefaultRunBehavior();
        void BeforeInitialize();
        void OnIsMouseVisibleChanged();
        void OnPresentationChanged();
        bool BeforeRun();
        void RunOnce();
        void RunLoop();
        void StartRunLoop();
        void Exit();
        bool BeforeUpdate();
        bool BeforeDraw();
        void EnterFullScreen();
        void ExitFullScreen();
        void BeginScreenDeviceChange(bool);
        void EndScreenDeviceChange(char*, int, int, int, int);
        void Log(char*);
        void Present();

    private:
        void SdlRunLoop();

    protected:
        Game* mGame;
        int mIsExiting;
        
    };
}