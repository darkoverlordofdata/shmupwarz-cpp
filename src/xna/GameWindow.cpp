#include "xna/GameWindow.h"

namespace xna {

    GameWindow::GameWindow() { }

    GameWindow::~GameWindow() {
    }


    bool GameWindow::getAllowResizing() { }
    bool GameWindow::setAllowResizing(bool) { }
    bool GameWindow::getBorderless() { }
    bool GameWindow::setBorderless(bool) { }
    Rectangle* GameWindow::getClientBounds() { }
    Point* GameWindow::getPosition() { }
    void GameWindow::setPosition(Point*) { }
    Point* GameWindow::getSize() { }

    bool GameWindow::getAllowAltF4() { 
        return allowAltF4;
    }
    void GameWindow::setAllowAltF4(bool allowAltF4) { 
        this->allowAltF4 = allowAltF4;
    }

    DisplayOrientation GameWindow::getCurentOrientation() { }
    SDL_Window* GameWindow::getHandle()  { }
    char* GameWindow::getScreenDeviceName()  { }

    char* GameWindow::getTitle() {
        return title;

    }

    void GameWindow::setTitle(char* title) {
        this->title = strdup(title);
    }

}