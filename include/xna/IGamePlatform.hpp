#pragma once
#include "IGameWindow.hpp"

namespace xna {

    class IGameWindow;
    class IGamePlatform {
    public:

        ~IGamePlatform() {}
        virtual bool InFullScreenMode() = 0;
        virtual GameRunBehavior DefaultRunBehavior() = 0;;
        virtual bool IsActive() = 0;
        virtual void IsActive(bool value) = 0;
        virtual bool IsMouseActive() = 0;
        virtual void IsMouseActive(bool value) = 0;
        virtual IGameWindow* Window() = 0;
        virtual void Window(IGameWindow* value) = 0;
        virtual void RaiseAsyncRunLoopEnded() = 0;
        virtual void BeforeInitialize() = 0;
        virtual bool BeforeRun() = 0;
        virtual void Exit() = 0;
        virtual void RunLoop() = 0;
        virtual void RunOnce() = 0;
        virtual void StartRunLoop() = 0;
        virtual bool BeforeUpdate() = 0;
        virtual bool BeforeDraw() = 0;
        virtual void EnterFullScreen() = 0;
        virtual void ExitFullScreen() = 0;
        virtual void BeginScreenDeviceChange (bool willBeFullScreen) = 0;
        virtual void EndScreenDeviceChange (
                    char* screenDeviceName,
                    int clientX,
                    int clientY,
                    int clientWidth,
                    int clientHeight
        ) = 0;
        virtual void Present() { }
        virtual void OnIsMouseVisibleChanged() = 0;
        virtual void OnPresentationChanged() = 0;
        virtual void Log(char* Message) = 0;		
        virtual void Dispose() = 0;

    };
}