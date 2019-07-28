#pragma once
#include "GameRunBehavior.hpp"
#include "IGame.hpp"
#include "IGameWindow.hpp"
#include "IGamePlatform.hpp"
#include "IFactory.hpp"

namespace xna {

    class IGame;
    class IGameWindow;
    class IFactory;   
    class GamePlatform : public IGamePlatform {
        protected:
        IGame* mGame;
        bool mInFullScreenMode = false;
        bool mIsActive;
        bool mIsMouseActive;
        IGameWindow* mWindow;

        public:
        GamePlatform() { }
        GamePlatform(IGame* game): mGame(game)
        { 
        }

        bool InFullScreenMode() {
            return mInFullScreenMode;
        }

        static IGamePlatform* PlatformCreate(IGame* game, IFactory* platform) {
            printf("In GamePlatform::PlatformCreate\n");
            
            if (game == nullptr) printf("game is null\n");
            if (platform == nullptr) printf("platform is null\n");
            // return nullptr;
            return platform->CreateGamePlatform(game);
        }

        GameRunBehavior DefaultRunBehavior() {};

        bool IsActive() {
            return mIsActive;
        }

        void IsActive(bool value) {
            if (mIsActive != value) {
                mIsActive = value;
                // EventHelpers.Raise()
            }
        }

        bool IsMouseActive() {
            return mIsMouseActive;
        }

        void IsMouseActive(bool value) {
            if (mIsMouseActive != value) {
                mIsMouseActive = value;
                // OnIsMouseVisibleChanged();
            }
        }

        IGameWindow* Window() {
            return mWindow;
        }

        void Window(IGameWindow* value) {
            if (mWindow != nullptr) {
                mWindow = value;
            }
        }

        /// <summary>
        /// Raises the AsyncRunLoopEnded event.  This method must be called by
        /// derived classes when the asynchronous run loop they start has
        /// stopped running.
        /// </summary>
        void RaiseAsyncRunLoopEnded() {
            // EventHelpers.Raise();
        }

        /// <summary>
        /// Gives derived classes an opportunity to do work before any
        /// components are initialized.  Note that the base implementation sets
        /// IsActive to true, so derived classes should either call the base
        /// implementation or set IsActive to true by their own means.
        /// </summary>
        void BeforeInitialize() {
            mIsActive = true;
        }

        /// <summary>
        /// Gives derived classes an opportunity to do work just before the
        /// run loop is begun.  Implementations may also return false to prevent
        /// the run loop from starting.
        /// </summary>
        /// <returns></returns>
        bool BeforeRun() {
            return true;
        }

        /// <summary>
        /// When implemented in a derived, ends the active run loop.
        /// </summary>
        void Exit() {}

        /// <summary>
        /// When implemented in a derived, starts the run loop and blocks
        /// until it has ended.
        /// </summary>
        void RunLoop() {}

        /// <summary>
        /// When implemented in a derived, runs the loop one time
        /// until it has ended.
        /// </summary>
        void RunOnce() {}

        /// <summary>
        /// When implemented in a derived, starts the run loop and returns
        /// immediately.
        /// </summary>
        void StartRunLoop() {}

        /// <summary>
        /// Gives derived classes an opportunity to do work just before Update
        /// is called for all IUpdatable components.  Returning false from this
        /// method will result in this round of Update calls being skipped.
        /// </summary>
        /// <param name="gameTime"></param>
        /// <returns></returns>
        bool BeforeUpdate() {}

        /// <summary>
        /// Gives derived classes an opportunity to do work just before Draw
        /// is called for all IDrawable components.  Returning false from this
        /// method will result in this round of Draw calls being skipped.
        /// </summary>
        /// <param name="gameTime"></param>
        /// <returns></returns>
        bool BeforeDraw() {}

        /// <summary>
        /// When implemented in a derived class, causes the game to enter
        /// full-screen mode.
        /// </summary>
        void EnterFullScreen() {}

        /// <summary>
        /// When implemented in a derived class, causes the game to exit
        /// full-screen mode.
        /// </summary>
        void ExitFullScreen() {}

        /// <summary>
        /// Starts a device transition (windowed to full screen or vice versa).
        /// </summary>
        /// <param name='willBeFullScreen'>
        /// Specifies whether the device will be in full-screen mode upon completion of the change.
        /// </param>
        void BeginScreenDeviceChange (
                    bool willBeFullScreen
        ) {}

        /// <summary>
        /// Completes a device transition.
        /// </summary>
        /// <param name='screenDeviceName'>
        /// Screen device name.
        /// </param>
        /// <param name='clientWidth'>
        /// The new width of the game's client window.
        /// </param>
        /// <param name='clientHeight'>
        /// The new height of the game's client window.
        /// </param>
        void EndScreenDeviceChange (
                    char* screenDeviceName,
                    int clientX,
                    int clientY,
                    int clientWidth,
                    int clientHeight
        ) {}

        void Present() { }

        void OnIsMouseVisibleChanged() {}

        /// <summary>
        /// Called by the GraphicsDeviceManager to notify the platform
        /// that the presentation parameters have changed.
        /// </summary>
        /// <param name="pp">The new presentation parameters.</param>
        void OnPresentationChanged() {}

        // /// <summary>
        // /// Log the specified Message.
        // /// </summary>
        // /// <param name='Message'>
        // /// 
        // /// </param>
        // [System.Diagnostics.Conditional("DEBUG")]
        void Log(char* Message) {}		


    };
}