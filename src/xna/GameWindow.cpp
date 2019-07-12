#include "xna/GameWindow.h"

namespace xna {

    GameWindow::GameWindow() { }

    GameWindow::~GameWindow() {
    }


    bool GameWindow::getAllowResizing() { }
    bool GameWindow::setAllowResizing(bool) { }
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

    bool GameWindow::getBorderless() { 
        return false;
    }
    bool GameWindow::setBorderless(bool) { 
        printf("GameWindow.IsBorderless");
    }

    void GameWindow::BeginScreenDeviceChange(bool) {}
    void GameWindow::EndScreenDeviceChange(char*, int, int, int, int) {}

    void GameWindow::OnClientSizeChanged() {
        // EventHelpers::Raise(this, ClientSizeChanged);
    }

    void GameWindow::OnTextInput(char c, Keys key) {
        // EventHelpers::Raise(this, TextInput);
    }
}