#pragma once
#include "DisplayOrientation.hpp"
#include "Rectangle.hpp"
#include "Point.hpp"
#include "../core/Core.hpp"

namespace xna {

    using core::Event;

    struct TextInputArgs {
        char c;
        Keys key;
    };
    class IGameWindow {
        
        public:
        ~IGameWindow() {}

        Event ClientSizeChanged;
        Event OrientationChanged;
        Event ScreenDeviceNameChanged;
        Event TextInput;

        virtual void SupportedOrientation(DisplayOrientation) = 0;
        virtual void BeginScreenDeviceChange(bool) = 0;
        virtual void EndScreenDeviceChange(char*, int, int, int, int) = 0;
        virtual bool AllowUserResizing() = 0;
        virtual bool AllowUserResizing(bool) = 0;
        virtual Rectangle* ClientBounds() = 0;
        virtual Point* Position() = 0;
        virtual void Position(Point*) = 0;
        virtual Point* Size() = 0;
        virtual bool AllowAltF4() = 0;
        virtual void AllowAltF4(bool allowAltF4) = 0;
        virtual DisplayOrientation CurentOrientation() = 0;
        virtual SDL_Window* Handle() = 0;
        virtual char* ScreenDeviceName() = 0;
        virtual char* Title() = 0;
        virtual void Title(char* title) = 0;
        virtual bool Borderless() = 0;
        virtual bool Borderless(bool) = 0;
        virtual void OnClientSizeChanged() = 0;
        virtual void OnOrientationChanged() = 0;
        virtual void OnScreenDeviceNameChanged() = 0;
        virtual void OnTextInput(char c, Keys key) = 0;
    };
}