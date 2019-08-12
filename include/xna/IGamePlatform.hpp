#pragma once
#include "IGameWindow.hpp"

namespace xna {

    class IGameWindow;
    class IGamePlatform {
    public:

        ~IGamePlatform() {}
        virtual bool InFullScreenMode() {}
        virtual GameRunBehavior DefaultRunBehavior() {};
        virtual bool IsActive() {}
        virtual void IsActive(bool value) {}
        virtual bool IsMouseActive() {}
        virtual void IsMouseActive(bool value) {}
        virtual IGameWindow* Window() {}
        virtual void Window(IGameWindow* value) {}
        virtual void RaiseAsyncRunLoopEnded() {}
        virtual void BeforeInitialize() {}
        virtual bool BeforeRun() {}
        virtual void Exit() {}
        virtual void RunLoop() {}
        virtual void RunOnce() {}
        virtual void StartRunLoop() {}
        virtual bool BeforeUpdate() {}
        virtual bool BeforeDraw() {}
        virtual void EnterFullScreen() {}
        virtual void ExitFullScreen() {}
        virtual void BeginScreenDeviceChange () {}
        virtual void EndScreenDeviceChange (
                    char* screenDeviceName,
                    int clientX,
                    int clientY,
                    int clientWidth,
                    int clientHeight
        ) {}
        virtual void Present() { }
        virtual void OnIsMouseVisibleChanged() {}
        virtual void OnPresentationChanged() {}
        virtual void Log(char* Message) {}		

    };
}