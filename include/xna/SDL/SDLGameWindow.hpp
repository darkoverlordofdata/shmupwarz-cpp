#pragma once

#include "../GameWindow.hpp"
#include "../GraphicsDeviceManager.hpp"

namespace xna {

    class Game;
    class SDLGameWindow : public GameWindow {
    friend class Game;
        
    public:

        SDLGameWindow() { }
        SDLGameWindow(Game* game) : GameWindow() {
            mGame = game;
            mWidth = GraphicsDeviceManager::DefaultBackBufferWidth;
            mHeight = GraphicsDeviceManager::DefaultBackBufferHeight;
            SDL_SetHint("SDL_VIDEO_MINIMIZE_ON_FOCUS_LOSS", "0");
            SDL_SetHint("SDL_JOYSTICK_ALLOW_BACKGROUND_EVENTS", "1");

            mHandle = SDL_GL_GetCurrentWindow();
            
        }

        void CreateWindow() {
            auto winx = SDL_WINDOWPOS_CENTERED;
            auto winy = SDL_WINDOWPOS_CENTERED;
            mHandle = SDL_GL_GetCurrentWindow();
            if (mIcon != nullptr)
                SDL_SetWindowIcon(mHandle, mIcon);

        }

        SDL_Window* Handle()  {
            return mHandle; 

        }

        bool AllowUserResizing() {
            return !mBorderless && mResizable;
        }

        bool AllowUserResizing(bool resizable) {
            if (mGame->SdlVersion() > 204) {
                SDL_SetWindowResizable(mHandle, (SDL_bool)mResizable);
            } else {
                printf("SDL 2.0.4 does not support changing resizable parameter of the window after it's already been created, please use a newer version of it.");
            }
            mResizable = resizable;
        }

        bool Borderless() {
            return mBorderless;
        }

        bool Borderless(bool borderless) {
            SDL_SetWindowBordered(mHandle, (SDL_bool)borderless);
            mBorderless = borderless;
        }

        Rectangle* ClientBounds() {
            int x = 0, y = 0;
            SDL_GetWindowPosition(mHandle, &x, &y);
            return new Rectangle(x, y, mWidth, mHeight);
        }

        DisplayOrientation CurentOrientation() { 
            return DisplayOrientation::Default; 
        }

        Point* Size() { 
            return new Point(mWidth, mHeight);
        }

        Point* Position() { 
            int x = 0, y = 0;
            SDL_GetWindowPosition(mHandle, &x, &y);
            return new Point(x, y);

        }
        void Position(Point* pos) { 
            SDL_SetWindowPosition(mHandle, pos->X, pos->Y);
            mWasMoved = true;
        }
        
        void Moved() {
            if (mSupressMove) {
                mSupressMove = false;
                return;
            }
            mWasMoved = true;
        }

        void ClientResize(int, int)  {   
            SDL_GetWindowSize(mHandle, &mWidth, &mHeight);
            GameWindow::OnClientSizeChanged();
        }

        void CallTextInput(char c, Keys key) {
            GameWindow::OnTextInput(c, key);
        }

        void SupportedOrientation(DisplayOrientation) {

        }

        void Title(char* title) {
            GameWindow::Title(title);
            SDL_SetWindowTitle(mHandle, title);
        }

        char* ScreenDeviceName()  { 
            return mScreenDeviceName;
        }

        void CursorVisible(bool visible) {
            mMouseVisible = visible;
            SDL_ShowCursor(visible);
        }

        void BeginScreenDeviceChange(bool willBeFullScreen) {
            mWillBeFullScreen = willBeFullScreen; 
        }
        
        void EndScreenDeviceChange(
            char* screenDeviceName, 
            int clientX, 
            int clientY, 
            int clientWidth, 
            int clientHeight
        ) {
            mScreenDeviceName = screenDeviceName;
            if (!mWillBeFullScreen) {
                SDL_SetWindowPosition(mHandle, clientX, clientY);
                SDL_SetWindowSize(mHandle, clientWidth, clientHeight);
                mWidth = clientWidth;
                mHeight = clientHeight;
                mX = clientX;
                mY = clientY;
            }
        }

    


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