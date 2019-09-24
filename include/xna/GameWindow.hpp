#pragma once
#include "DisplayOrientation.hpp"
#include "Input/Keys.hpp"
#include "IGameWindow.hpp"
#include "Rectangle.hpp"
#include "Point.hpp"
#include "core/Core.hpp"

namespace xna {

    using core::Event;

    // struct TextInputArgs {
    //     char c;
    //     Keys key;
    // };
    class GameWindow : public IGameWindow {
        
        public:


        GameWindow() { }

        ~GameWindow() {}

        Event ClientSizeChanged = Event();
        Event OrientationChanged = Event();
        Event ScreenDeviceNameChanged = Event();
        Event TextInput = Event();

        // virtual void SupportedOrientation(DisplayOrientation) = 0;
        // virtual void BeginScreenDeviceChange(bool) = 0;
        // virtual void EndScreenDeviceChange(char*, int, int, int, int) = 0;
        // virtual bool AllowUserResizing() { }
        // virtual bool AllowUserResizing(bool) { }
        // virtual Rectangle* ClientBounds() { }
        // virtual Point* Position() { }
        // virtual void Position(Point*) { }
        // virtual Point* Size() { }

        virtual bool AllowAltF4() { 
            return mAllowAltF4;
        }
        virtual void AllowAltF4(bool allowAltF4) { 
            mAllowAltF4 = allowAltF4;
        }

        // virtual DisplayOrientation CurentOrientation() { }
        // virtual SDL_Window* Handle()  { }
        // virtual char* ScreenDeviceName()  { }

        char* Title() override {
            return mTitle;

        }

        void Title(char* title) override {
            mTitle = strdup(title);
        }

        virtual bool Borderless() { 
            return false;
        }
        virtual bool Borderless(bool) { 
            printf("GameWindow.IsBorderless");
        }

        void OnClientSizeChanged() override {
            ClientSizeChanged (this, nullptr);
        }

        void OnOrientationChanged() override {
            OrientationChanged(this, nullptr);
        }

        void OnScreenDeviceNameChanged() override {
            ScreenDeviceNameChanged(this, nullptr);
        }

        void OnTextInput(char c, Keys key) override {
            TextInputArgs args = {c, key};
            TextInput(this, &args);
        }


        protected:
        bool mAllowUserResizing;
        bool mAllowAltF4 = true;
        char* mTitle;
        char* mScreenDeviceName;

    };
}