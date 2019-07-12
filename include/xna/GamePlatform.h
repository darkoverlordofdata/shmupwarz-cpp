#pragma once
#include "GameBase.h"
#include "GameWindow.h"
#include "GameRunBehavior.h"

namespace xna {

    class GameBase;
    class GameWindow;
    class GamePlatform {
        
    public:
        GamePlatform();
        GamePlatform(GameBase* game);
        ~GamePlatform();    

        static GamePlatform* PlatformCreate(GameBase*);
        // virtual GameRunBehavior getDefaultRunBehavior() = 0;
        // bool getActive();
        // void setActive(bool);
        // bool getMouseActive();
        // void setMouseActive();
        // void RaiseAsyncRunLoopEnded();


    // private:
        GameBase* game;
        bool needsToResetElapsedTime = false;
        bool disposed;
        bool inFullScreenMode = false;
        bool isActive;
        bool isMouseActive;
        GameWindow* window;
    };
}