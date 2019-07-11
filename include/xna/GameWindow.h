#pragma once
#include "Game.h"
#include "Rectangle.h"
#include "Point.h"
#include "DisplayOrientation.h"

namespace xna {

    class GameWindow {
        
    public:
        GameWindow();
        ~GameWindow();    

        virtual bool getAllowResizing() = 0;
        virtual bool setAllowResizing(bool) = 0;
        virtual bool getBorderless() = 0;
        virtual bool setBorderless(bool) = 0;
        virtual Rectangle* getClientBounds() = 0;
        virtual Point* getPosition() = 0;
        virtual void setPosition(Point*) = 0;
        virtual Point* getSize() = 0;
        virtual bool getAllowAltF4();
        virtual void setAllowAltF4(bool);
        virtual DisplayOrientation getCurentOrientation() = 0;
        virtual SDL_Window* getHandle() = 0;
        virtual char* getScreenDeviceName() = 0;

        char* getTitle();
        void setTitle(char*);
        


        bool allowAltF4 = true;
        char* title;
        char* screenDeviceName;

    };
}