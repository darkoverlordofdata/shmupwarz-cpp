#pragma once
#include "Game.h"
#include "GameWindow.h"
#include "GameRunBehavior.h"

namespace xna {

    class Game;
    class GameWindow;
    class GamePlatform {
        
    public:
        GamePlatform();
        GamePlatform(Game* game);
        ~GamePlatform();    

        bool InFullScreenMode();
        static GamePlatform* PlatformCreate(Game*);
        virtual GameRunBehavior DefaultRunBehavior() = 0;
        bool IsActive();
        void IsActive(bool);
        bool IsMouseActive();
        void IsMouseActive(bool);
        GameWindow* Window();
        void Window(GameWindow*);
        void RaiseAsyncRunLoopEnded();
        virtual void BeforeInitialize();
        virtual bool BeforeRun();
        virtual void Exit() = 0;
        virtual void RunLoop() = 0;
        virtual void RunOnce() = 0;
        virtual void StartRunLoop() = 0;
        virtual bool BeforeUpdate() = 0;
        virtual bool BeforeDraw() = 0;
        virtual void EnterFullScreen() = 0;
        virtual void ExitFullScreen() = 0;
        virtual void BeginScreenDeviceChange(bool);
        virtual void EndScreenDeviceChange(char*, int, int, int, int) = 0;
        virtual void OnIsMouseVisibleChanged() = 0;
        virtual void OnPresentationChanged() = 0;
        virtual void Log(char*) = 0;
        virtual void Present() = 0;


    protected:
        Game* mGame;
        bool mInFullScreenMode = false;
        bool mIsActive;
        bool mIsMouseActive;
        GameWindow* mWindow;

    };
}