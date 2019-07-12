#include "xna/SDL/SDLGameWindow.h"
#include "xna/GraphicsDeviceManager.h"

namespace xna {

    SDLGameWindow::SDLGameWindow() { }
    SDLGameWindow::SDLGameWindow(GameBase* game) : GameWindow() {
        this->game = game;
        width = GraphicsDeviceManager::DefaultBackBufferWidth;
        height = GraphicsDeviceManager::DefaultBackBufferHeight;
        SDL_SetHint("SDL_VIDEO_MINIMIZE_ON_FOCUS_LOSS", "0");
        SDL_SetHint("SDL_JOYSTICK_ALLOW_BACKGROUND_EVENTS", "1");

        handle = SDL_GL_GetCurrentWindow();
        
    }

    void SDLGameWindow::CreateWindow() {
        auto winx = SDL_WINDOWPOS_CENTERED;
        auto winy = SDL_WINDOWPOS_CENTERED;
        handle = SDL_GL_GetCurrentWindow();
        if (icon != nullptr)
            SDL_SetWindowIcon(handle, icon);

    }

    SDL_Window* SDLGameWindow::getHandle()  {
        return handle; 

    }

    bool SDLGameWindow::getAllowResizing() {
        return !borderless && resizable;
    }

    bool SDLGameWindow::setAllowResizing(bool resizable) {
        if (game->SdlVersion > 204) {
            SDL_SetWindowResizable(handle, (SDL_bool)resizable);
        } else {
            printf("SDL 2.0.4 does not support changing resizable parameter of the window after it's already been created, please use a newer version of it.");
        }
        this->resizable = resizable;
    }

    bool SDLGameWindow::getBorderless() {
        return this->borderless;
    }

    bool SDLGameWindow::setBorderless(bool borderless) {
        SDL_SetWindowBordered(handle, (SDL_bool)borderless);
        this->borderless = borderless;
    }

    Rectangle* SDLGameWindow::getClientBounds() {
        int x = 0, y = 0;
        SDL_GetWindowPosition(handle, &x, &y);
        return new Rectangle(x, y, width, height);
    }

    DisplayOrientation SDLGameWindow::getCurentOrientation() { 
        return DisplayOrientation::Default; 
    }

    Point* SDLGameWindow::getSize() { 
        return new Point(width, height);
    }

    Point* SDLGameWindow::getPosition() { 
        int x = 0, y = 0;
        SDL_GetWindowPosition(handle, &x, &y);
        return new Point(x, y);

    }
    void SDLGameWindow::setPosition(Point* pos) { 
        SDL_SetWindowPosition(handle, pos->X, pos->Y);
        wasMoved = true;
    }
    
    void SDLGameWindow::Moved() {
        if (supressMove) {
            supressMove = false;
            return;
        }
        wasMoved = true;
    }

    void SDLGameWindow::ClientResize(int, int)  {   
        SDL_GetWindowSize(handle, &width, &height);
        GameWindow::OnClientSizeChanged();
    }

    void SDLGameWindow::CallTextInput(char c, Keys key) {
        GameWindow::OnTextInput(c, key);
    }

    void SDLGameWindow::setSupportedOrientation(DisplayOrientation) {

    }

    void SDLGameWindow::setTitle(char* title) {
        GameWindow::setTitle(title);
        SDL_SetWindowTitle(handle, title);
    }

    char* SDLGameWindow::getScreenDeviceName()  { 
        return screenDeviceName;
    }

    void SDLGameWindow::setCursorVisible(bool visible) {
        mouseVisible = visible;
        SDL_ShowCursor(visible);
    }

    void SDLGameWindow::BeginScreenDeviceChange(bool willBeFullScreen) {
        this->willBeFullScreen = willBeFullScreen; 
    }
    
    void SDLGameWindow::EndScreenDeviceChange(
        char* screenDeviceName, 
        int clientX, 
        int clientY, 
        int clientWidth, 
        int clientHeight
    ) {
        this->screenDeviceName = screenDeviceName;
        if (!willBeFullScreen) {
            SDL_SetWindowPosition(handle, clientX, clientY);
            SDL_SetWindowSize(handle, clientWidth, clientHeight);
            width = clientWidth;
            height = clientHeight;
            x = clientX;
            y = clientY;
        }
    }

    


}