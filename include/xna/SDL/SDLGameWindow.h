#pragma once

#include "../GamePlatform.h"
#include "../GameWindow.h"

namespace xna {

    class GameBase;
    class SDLGameWindow : public GameWindow {
    friend class GameBase;
        
    public:
        SDLGameWindow();
        SDLGameWindow(GameBase* game);
        ~SDLGameWindow();

        virtual SDL_Window* getHandle() override;

        void CreateWindow();
        bool getAllowResizing() override;
        bool setAllowResizing(bool) override;
        virtual void setTitle(char*);
        bool getBorderless() override;
        bool setBorderless(bool) override;
        Rectangle* getClientBounds() override;
        virtual DisplayOrientation getCurentOrientation() override;
        virtual Point* getSize() override;
        virtual Point* getPosition() override;
        virtual void setPosition(Point*) override;

        void Moved();
        void ClientResize(int, int);
        void CallTextInput(char, Keys);
        virtual void setSupportedOrientation(DisplayOrientation) override;

        virtual char* getScreenDeviceName() override;
        void setCursorVisible(bool);
        virtual void BeginScreenDeviceChange(bool) override;
        virtual void EndScreenDeviceChange(char*, int, int, int, int) override;

        GameBase* game;
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