#include "xna/SDL/SDLGameWindow.h"
#include "xna/GraphicsDeviceManager.h"

namespace xna {

    SDLGameWindow::SDLGameWindow() { }
    SDLGameWindow::SDLGameWindow(Game* game) : GameWindow() {
        mGame = game;
        mWidth = GraphicsDeviceManager::DefaultBackBufferWidth;
        mHeight = GraphicsDeviceManager::DefaultBackBufferHeight;
        SDL_SetHint("SDL_VIDEO_MINIMIZE_ON_FOCUS_LOSS", "0");
        SDL_SetHint("SDL_JOYSTICK_ALLOW_BACKGROUND_EVENTS", "1");

        mHandle = SDL_GL_GetCurrentWindow();
        
    }

    void SDLGameWindow::CreateWindow() {
        auto winx = SDL_WINDOWPOS_CENTERED;
        auto winy = SDL_WINDOWPOS_CENTERED;
        mHandle = SDL_GL_GetCurrentWindow();
        if (mIcon != nullptr)
            SDL_SetWindowIcon(mHandle, mIcon);

    }

    SDL_Window* SDLGameWindow::Handle()  {
        return mHandle; 

    }

    bool SDLGameWindow::AllowUserResizing() {
        return !mBorderless && mResizable;
    }

    bool SDLGameWindow::AllowUserResizing(bool resizable) {
        if (mGame->SdlVersion() > 204) {
            SDL_SetWindowResizable(mHandle, (SDL_bool)mResizable);
        } else {
            printf("SDL 2.0.4 does not support changing resizable parameter of the window after it's already been created, please use a newer version of it.");
        }
        mResizable = resizable;
    }

    bool SDLGameWindow::Borderless() {
        return mBorderless;
    }

    bool SDLGameWindow::Borderless(bool borderless) {
        SDL_SetWindowBordered(mHandle, (SDL_bool)borderless);
        mBorderless = borderless;
    }

    Rectangle* SDLGameWindow::ClientBounds() {
        int x = 0, y = 0;
        SDL_GetWindowPosition(mHandle, &x, &y);
        return new Rectangle(x, y, mWidth, mHeight);
    }

    DisplayOrientation SDLGameWindow::CurentOrientation() { 
        return DisplayOrientation::Default; 
    }

    Point* SDLGameWindow::Size() { 
        return new Point(mWidth, mHeight);
    }

    Point* SDLGameWindow::Position() { 
        int x = 0, y = 0;
        SDL_GetWindowPosition(mHandle, &x, &y);
        return new Point(x, y);

    }
    void SDLGameWindow::Position(Point* pos) { 
        SDL_SetWindowPosition(mHandle, pos->X, pos->Y);
        mWasMoved = true;
    }
    
    void SDLGameWindow::Moved() {
        if (mSupressMove) {
            mSupressMove = false;
            return;
        }
        mWasMoved = true;
    }

    void SDLGameWindow::ClientResize(int, int)  {   
        SDL_GetWindowSize(mHandle, &mWidth, &mHeight);
        GameWindow::OnClientSizeChanged();
    }

    void SDLGameWindow::CallTextInput(char c, Keys key) {
        GameWindow::OnTextInput(c, key);
    }

    void SDLGameWindow::SupportedOrientation(DisplayOrientation) {

    }

    void SDLGameWindow::Title(char* title) {
        GameWindow::Title(title);
        SDL_SetWindowTitle(mHandle, title);
    }

    char* SDLGameWindow::ScreenDeviceName()  { 
        return mScreenDeviceName;
    }

    void SDLGameWindow::CursorVisible(bool visible) {
        mMouseVisible = visible;
        SDL_ShowCursor(visible);
    }

    void SDLGameWindow::BeginScreenDeviceChange(bool willBeFullScreen) {
        mWillBeFullScreen = willBeFullScreen; 
    }
    
    void SDLGameWindow::EndScreenDeviceChange(
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

    


}