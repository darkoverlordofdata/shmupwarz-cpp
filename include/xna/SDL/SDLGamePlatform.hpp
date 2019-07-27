#pragma once
#include "../GamePlatform.hpp"
#include "SDLGameWindow.hpp"

namespace xna {

    class Game;
    class SDLGameWindow;
    class SDLGamePlatform : public GamePlatform {
    friend class Game;
        
    public:

        SDLGamePlatform() { }
        SDLGamePlatform(Game* game) : GamePlatform(game) {
            printf("SDLGamePlatform ctor\n");
            mGame = game;
            mKeys = new std::list<Keys>();
            // Keyboard.SetKeys(mKeys);

            SDL_version sversion;
            SDL_GetVersion(&sversion);
            int version = 100 * sversion.major + 10 * sversion.minor + sversion.patch;
            // game->SetSdlVersion(version);
            game->SdlVersion(version);
            if (version <= 204) {
                printf("Please use SDL 2.0.5 or higher.\n");

            }
            SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO);
            SDL_DisableScreenSaver();

            mWindow = new SDLGameWindow(game);
            mView = (SDLGameWindow*)mWindow;
            

        }

        ~SDLGamePlatform() {
        }

        GameRunBehavior DefaultRunBehavior() {
            return GameRunBehavior::Synchronous;
        }

        void BeforeInitialize() {
            SdlRunLoop();
            GamePlatform::BeforeInitialize();
        }

        void OnIsMouseVisibleChanged() {
            // mView->SetCursorVisible(mGame->IsMouseVisible());
        }

        void OnPresentationChanged() {
                // var displayIndex = Sdl.Window.GetDisplayIndex(Window.Handle);
                // var displayName = Sdl.Display.GetDisplayName(displayIndex);
                // BeginScreenDeviceChange(pp.IsFullScreen);
                // EndScreenDeviceChange(displayName, pp.WindowPositionX, pp.WindowPositionY, pp.BackBufferWidth, pp.BackBufferHeight);
        }

        bool BeforeRun()
        {
            // Sdl.Window.Show(Window.Handle);
            // print("Platform::BeforeRun\n");
            return true;
        }

        void RunOnce() {
                // // print("Platform::RunOnce %f\n", Game.gameTime.ElapsedGameTime.TotalMilliseconds);
                // SdlRunLoop();
                // Game.Tick();
                // // Threading.Run();
                // GraphicsDevice.DisposeContexts();
        }

        void RunLoop() {
                // Sdl.Window.Show(Window.Handle);

                // while (true)
                // {
                //     SdlRunLoop();
                //     Game.Tick();
                //     // Threading.Run();
                //     GraphicsDevice.DisposeContexts();

                //     if (_isExiting > 0)
                //         break;
                // }

        }

        void SdlRunLoop()
        {
            // Sdl.Event ev;

            // while (Sdl.PollEvent(out ev) == 1)
            // {
            //     if (ev.Type == Sdl.EventType.Quit)
            //         _isExiting++;

            //     else if (ev.Type == Sdl.EventType.JoyDeviceAdded)
            //         Joystick.AddDevice(ev.JoystickDevice.Which);
            //     else if (ev.Type == Sdl.EventType.ControllerDeviceRemoved)
            //         GamePad.RemoveDevice(ev.ControllerDevice.Which);
            //     else if (ev.Type == Sdl.EventType.JoyDeviceRemoved)
            //         Joystick.RemoveDevice(ev.JoystickDevice.Which);
            //     else if (ev.Type == Sdl.EventType.MouseWheel)
            //     {
            //         const int wheelDelta = 120;
            //         Mouse.ScrollY += ev.Wheel.Y * wheelDelta;
            //         Mouse.ScrollX += ev.Wheel.X * wheelDelta;
            //     }
            //     else if (ev.Type == Sdl.EventType.MouseMotion)
            //     {
            //         Window.MouseState.X = ev.Motion.X;
            //         Window.MouseState.Y = ev.Motion.Y;
            //     }
            //     else if (ev.Type == Sdl.EventType.MouseButtonDown)
            //     {
            //         // print("Button Down (%d, %d)\n", ev.Button.Button, ev.Button.State);

            //         if (ev.Button.Button == 1)
            //             Window.MouseState.LeftButton = ButtonState.Pressed;
            //         if (ev.Button.Button == 2)
            //             Window.MouseState.MiddleButton = ButtonState.Pressed;
            //         if (ev.Button.Button == 3)
            //             Window.MouseState.RightButton = ButtonState.Pressed;
                    
            //     }
            //     else if (ev.Type == Sdl.EventType.MouseButtonup)
            //     {
            //         // print("Button Up (%d, %d)\n", ev.Button.Button, ev.Button.State);

            //         if (ev.Button.Button == 1)
            //             Window.MouseState.LeftButton = ButtonState.Released;
            //         if (ev.Button.Button == 2)
            //             Window.MouseState.MiddleButton = ButtonState.Released;
            //         if (ev.Button.Button == 3)
            //             Window.MouseState.RightButton = ButtonState.Released;

            //     }
            //     else if (ev.Type == Sdl.EventType.KeyDown)
            //     {
            //         var key = KeyboardUtil.ToXna(ev.Key.Keysym.Sym);
            //         if (!_keys.Contains(key))
            //             _keys.Add(key);
            //         char character = (char)ev.Key.Keysym.Sym;
            //         if (character.iscntrl())
            //             _view.CallTextInput(character, key);
            //     }
            //     else if (ev.Type == Sdl.EventType.KeyUp)
            //     {
            //         var key = KeyboardUtil.ToXna(ev.Key.Keysym.Sym);
            //         _keys.Remove(key);
            //     }
            //     else if (ev.Type == Sdl.EventType.TextInput)
            //     {
            //         int len = 0;
            //         string text = ""; //String.Empty;
            //         while (ev.Text.Text[len] != 0) {
            //         // while (Marshal.ReadByte ((IntPtr)ev.Text.Text, len) != 0) {
            //             len++;
            //         }
            //         // Marshal.Copy ((IntPtr)ev.Text.Text, buffer, 0, len);
            //         // text = System.Text.Encoding.UTF8.GetString (buffer);
            //         var buffer = new uint8 [len];
            //         Memory.copy(buffer, ev.Text.Text, len);
            //         text = (string)buffer;
            //         if (text.length == 0)
            //             continue;
            //         foreach (var c in buffer)// text)
            //         {
            //             var key = KeyboardUtil.ToXna((int)c);
            //             _view.CallTextInput((char)c, key);
            //         }
            //     }
            //     else if (ev.Type == Sdl.EventType.WindowEvent)
            //     {
            //         if (ev.Window.EventID == Sdl.Window.EventId.Resized || ev.Window.EventID == Sdl.Window.EventId.SizeChanged)
            //             _view.ClientResize(ev.Window.Data1, ev.Window.Data2);
            //         else if (ev.Window.EventID == Sdl.Window.EventId.FocusGained)
            //             IsActive = true;
            //         else if (ev.Window.EventID == Sdl.Window.EventId.FocusLost)
            //             IsActive = false;
            //         else if (ev.Window.EventID == Sdl.Window.EventId.Moved)
            //             _view.Moved();
            //     }
            // }
        }



        void StartRunLoop() {
                // throw new Exception.NotSupportedException("The desktop platform does not support asynchronous run loops");
        }

        void Exit(){
            mIsExiting++;
        }

        bool BeforeUpdate(){
            return true;
        }

        bool BeforeDraw(){
            return true;
        }

        void EnterFullScreen()
        {
        }

        void ExitFullScreen()
        {
        }

        void BeginScreenDeviceChange (
                    bool willBeFullScreen
        ) {}

        void EndScreenDeviceChange (
                    char* screenDeviceName,
                    int clientX,
                    int clientY,
                    int clientWidth,
                    int clientHeight
        ) {}

        void Present() { }

        // /// <summary>
        // /// Log the specified Message.
        // /// </summary>
        // /// <param name='Message'>
        // /// 
        // /// </param>
        // [System.Diagnostics.Conditional("DEBUG")]
        void Log(char* Message) {}		

    // private:
    //     void SdlRunLoop();

    protected:
        Game* mGame;
        std::list<Keys>* mKeys;
        int mIsExiting;
        SDLGameWindow* mView;

        
    };
}