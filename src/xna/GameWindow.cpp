#include "xna/GameWindow.h"

namespace xna {

    GameWindow::GameWindow() { }

    GameWindow::~GameWindow() {
    }


    bool GameWindow::AllowUserResizing() { }
    bool GameWindow::AllowUserResizing(bool) { }
    Rectangle* GameWindow::ClientBounds() { }
    Point* GameWindow::Position() { }
    void GameWindow::Position(Point*) { }
    Point* GameWindow::Size() { }

    bool GameWindow::AllowAltF4() { 
        return mAllowAltF4;
    }
    void GameWindow::AllowAltF4(bool allowAltF4) { 
        mAllowAltF4 = allowAltF4;
    }

    DisplayOrientation GameWindow::CurentOrientation() { }
    SDL_Window* GameWindow::Handle()  { }
    char* GameWindow::ScreenDeviceName()  { }

    char* GameWindow::Title() {
        return mTitle;

    }

    void GameWindow::Title(char* title) {
        mTitle = strdup(title);
    }

    bool GameWindow::Borderless() { 
        return false;
    }
    bool GameWindow::Borderless(bool) { 
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