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

        static GamePlatform* PlatformCreate(Game*);
        // virtual GameRunBehavior getDefaultRunBehavior() = 0;
        // bool getActive();
        // void setActive(bool);
        // bool getMouseActive();
        // void setMouseActive();
        // void RaiseAsyncRunLoopEnded();


    protected:
        GameWindow* mWindow;
        Game* mGame;
        bool mNeedsToResetElapsedTime = false;
        bool mDisposed;
        bool mInFullScreenMode = false;
        bool mIsActive;
        bool mIsMouseActive;
    };
}