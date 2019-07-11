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

        void CreateWindow();
        bool getAllowResizing() override;
        bool setAllowResizing(bool) override;
        bool getBorderless() override;
        bool setBorderless(bool) override;
        Rectangle* getClientBounds() override;
        virtual Point* getPosition() override;
        virtual void setPosition(Point*) override;
        virtual Point* getSize() override;

        virtual DisplayOrientation getCurentOrientation() override;
        virtual SDL_Window* getHandle() override;
        virtual char* getScreenDeviceName() override;

        Game* game;
        SDL_Window* handle;
        char* title;
        int x;
        int y;
        int width;
        int height;
        bool wasMoved;
        bool supressMove;
        SDL_Surface* icon;
        bool resizable;
        bool borderless;
        bool willBeFullScreen;
        bool mouseVisible;
        bool hardwareSwitch;
        char* screenDeviceName;
        
    };
}