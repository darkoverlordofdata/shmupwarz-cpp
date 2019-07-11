#include "xna/SDL/SDLGameWindow.h"
#include "xna/GraphicsDeviceManager.h"

namespace xna {

    SDLGameWindow::SDLGameWindow() { }
    SDLGameWindow::SDLGameWindow(Game* game) : GameWindow() {
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

    bool SDLGameWindow::getAllowResizing() {
        return !borderless && resizable;
    }

    bool SDLGameWindow::setAllowResizing(bool resizable) {
        if (game->sdlVersion > 204) {
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

    Point* SDLGameWindow::getSize() { 
        return new Point(width, height);
    }

    Point* SDLGameWindow::getPosition() { 
        int x = 0, y = 0;
        SDL_GetWindowPosition(handle, &x, &y);
        return new Point(x, y);

    }
    void SDLGameWindow::setPosition(Point* pos) { 
        SDL_SetWindowPosition(handle, pos->x, pos->y);
        wasMoved = true;
    }

    DisplayOrientation SDLGameWindow::getCurentOrientation() { 
        return DisplayOrientation::Default; 
    }
    SDL_Window* SDLGameWindow::getHandle()  {
        return handle; 

    }
    char* SDLGameWindow::getScreenDeviceName()  { 
        return screenDeviceName;
    }


}