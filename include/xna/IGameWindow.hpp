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
        virtual bool AllowUserResizing() { }
        virtual bool AllowUserResizing(bool) { }
        virtual Rectangle* ClientBounds() { }
        virtual Point* Position() { }
        virtual void Position(Point*) { }
        virtual Point* Size() { }
        virtual bool AllowAltF4() { }
        virtual void AllowAltF4(bool allowAltF4) { }
        virtual DisplayOrientation CurentOrientation() { }
        virtual SDL_Window* Handle()  { }
        virtual char* ScreenDeviceName()  { }
        char* Title() {}
        void Title(char* title) {}
        virtual bool Borderless() {}
        virtual bool Borderless(bool) {}
        void OnClientSizeChanged() {}
        void OnOrientationChanged() {}
        void OnScreenDeviceNameChanged() {}
        void OnTextInput(char c, Keys key) {}
    };
}