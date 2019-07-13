#pragma once
#include "Game.h"
#include "Rectangle.h"
#include "Point.h"
#include "DisplayOrientation.h"
#include "Input/Keys.h"

namespace xna {

    class GameWindow {
        
    public:
        GameWindow();
        ~GameWindow();    

        virtual bool AllowUserResizing() = 0;
        virtual bool AllowUserResizing(bool) = 0;
        virtual Rectangle* ClientBounds() = 0;
        virtual Point* Position() = 0;
        virtual void Position(Point*) = 0;
        virtual Point* Size() = 0;
        virtual bool AllowAltF4();
        virtual void AllowAltF4(bool);
        virtual DisplayOrientation CurentOrientation() = 0;
        virtual SDL_Window* Handle() = 0;
        virtual char* ScreenDeviceName() = 0;

        char* Title();
        virtual void Title(char*);
        virtual bool Borderless();
        virtual bool Borderless(bool);
        virtual void SupportedOrientation(DisplayOrientation) = 0;
        virtual void BeginScreenDeviceChange(bool) = 0;
        virtual void EndScreenDeviceChange(char*, int, int, int, int) = 0;

        void OnClientSizeChanged();
        void OnTextInput(char, Keys);

    protected:
        bool mAllowUserResizing;
        bool mAllowAltF4 = true;
        char* mTitle;
        char* mScreenDeviceName;

    };
}