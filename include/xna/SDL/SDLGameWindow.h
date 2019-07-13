#pragma once

#include "../GamePlatform.h"
#include "../GameWindow.h"

namespace xna {

    class Game;
    class SDLGameWindow : public GameWindow {
    friend class Game;
        
    public:
        SDLGameWindow();
        SDLGameWindow(Game* game);
        ~SDLGameWindow();

        virtual SDL_Window* Handle() override;

        void CreateWindow();
        bool AllowUserResizing() override;
        bool AllowUserResizing(bool) override;
        virtual void Title(char*);
        bool Borderless() override;
        bool Borderless(bool) override;
        Rectangle* ClientBounds() override;
        virtual DisplayOrientation CurentOrientation() override;
        virtual Point* Size() override;
        virtual Point* Position() override;
        virtual void Position(Point*) override;

        void Moved();
        void ClientResize(int, int);
        void CallTextInput(char, Keys);
        virtual void SupportedOrientation(DisplayOrientation) override;

        virtual char* ScreenDeviceName() override;
        void CursorVisible(bool);
        virtual void BeginScreenDeviceChange(bool) override;
        virtual void EndScreenDeviceChange(char*, int, int, int, int) override;

    protected:
        Game* mGame;
        SDL_Window* mHandle;
        char* mTitle;
        int mX;
        int mY;
        int mWidth;
        int mHeight;
        bool mWasMoved;
        bool mSupressMove;
        SDL_Surface* mIcon;
        bool mResizable;
        bool mBorderless;
        bool mWillBeFullScreen;
        bool mMouseVisible;
        bool mHardwareSwitch;
        char* mScreenDeviceName;
        
    };
}