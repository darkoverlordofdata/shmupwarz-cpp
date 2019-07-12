#pragma once
#include "GameBase.h"
#include "Rectangle.h"
#include "Point.h"
#include "DisplayOrientation.h"
#include "Input/Keys.h"

namespace xna {

    class GameWindow {
        
    public:
        GameWindow();
        ~GameWindow();    

        virtual bool getAllowResizing() = 0;
        virtual bool setAllowResizing(bool) = 0;
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
        virtual void setTitle(char*);
        virtual bool getBorderless();
        virtual bool setBorderless(bool);
        virtual void setSupportedOrientation(DisplayOrientation) = 0;
        virtual void BeginScreenDeviceChange(bool) = 0;
        virtual void EndScreenDeviceChange(char*, int, int, int, int) = 0;\

        void OnClientSizeChanged();
        void OnTextInput(char, Keys);

    private:
        bool allowAltF4 = true;
        char* title;
        char* screenDeviceName;

    };
}