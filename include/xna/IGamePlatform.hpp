#pragma once
#include "IGameWindow.hpp"

namespace xna {

    class IGameWindow;
    class IGamePlatform {
    public:

        ~IGamePlatform() {}
        bool InFullScreenMode() {}
        GameRunBehavior DefaultRunBehavior() {};
        bool IsActive() {}
        void IsActive(bool value) {}
        bool IsMouseActive() {}
        void IsMouseActive(bool value) {}
        IGameWindow* Window() {}
        void Window(IGameWindow* value) {}
        void RaiseAsyncRunLoopEnded() {}
        void BeforeInitialize() {}
        bool BeforeRun() {}
        void Exit() {}
        void RunLoop() {}
        void RunOnce() {}
        void StartRunLoop() {}
        bool BeforeUpdate() {}
        bool BeforeDraw() {}
        void EnterFullScreen() {}
        void ExitFullScreen() {}
        void BeginScreenDeviceChange () {}
        void EndScreenDeviceChange (
                    char* screenDeviceName,
                    int clientX,
                    int clientY,
                    int clientWidth,
                    int clientHeight
        ) {}
        void Present() { }
        void OnIsMouseVisibleChanged() {}
        void OnPresentationChanged() {}
        void Log(char* Message) {}		

    };
}