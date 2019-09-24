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

        bool InFullScreenMode() override {
            return mInFullScreenMode;
        }

        static IGamePlatform* PlatformCreate(IGame* game, IFactory* platform) {
            printf("In GamePlatform::PlatformCreate\n");
            
            assert(game);
            assert(platform);
            return platform->CreateGamePlatform(game);
        }

        // GameRunBehavior DefaultRunBehavior() override {};

        bool IsActive() override {
            return mIsActive;
        }

        void IsActive(bool value) override {
            if (mIsActive != value) {
                mIsActive = value;
                // EventHelpers.Raise()
            }
        }

        bool IsMouseActive() override {
            return mIsMouseActive;
        }

        void IsMouseActive(bool value) override {
            if (mIsMouseActive != value) {
                mIsMouseActive = value;
                // OnIsMouseVisibleChanged();
            }
        }

        IGameWindow* Window() override {
            return mWindow;
        }

        void Window(IGameWindow* value) override {
            if (mWindow != nullptr) {
                mWindow = value;
            }
        }

        /// <summary>
        /// Raises the AsyncRunLoopEnded event.  This method must be called by
        /// derived classes when the asynchronous run loop they start has
        /// stopped running.
        /// </summary>
        void RaiseAsyncRunLoopEnded() override {
            // EventHelpers.Raise();
        }

        /// <summary>
        /// Gives derived classes an opportunity to do work before any
        /// components are initialized.  Note that the base implementation sets
        /// IsActive to true, so derived classes should either call the base
        /// implementation or set IsActive to true by their own means.
        /// </summary>
        void BeforeInitialize() override {
            mIsActive = true;
        }

        /// <summary>
        /// Gives derived classes an opportunity to do work just before the
        /// run loop is begun.  Implementations may also return false to prevent
        /// the run loop from starting.
        /// </summary>
        /// <returns></returns>
        bool BeforeRun() override {
            return true;
        }

        /// <summary>
        /// When implemented in a derived, ends the active run loop.
        /// </summary>
        void Exit() override {}

        /// <summary>
        /// When implemented in a derived, starts the run loop and blocks
        /// until it has ended.
        /// </summary>
        void RunLoop() override {}

        /// <summary>
        /// When implemented in a derived, runs the loop one time
        /// until it has ended.
        /// </summary>
        void RunOnce() override {}

        /// <summary>
        /// When implemented in a derived, starts the run loop and returns
        /// immediately.
        /// </summary>
        void StartRunLoop() override {}

        /// <summary>
        /// Gives derived classes an opportunity to do work just before Update
        /// is called for all IUpdatable components.  Returning false from this
        /// method will result in this round of Update calls being skipped.
        /// </summary>
        /// <param name="gameTime"></param>
        /// <returns></returns>
        bool BeforeUpdate() override {}

        /// <summary>
        /// Gives derived classes an opportunity to do work just before Draw
        /// is called for all IDrawable components.  Returning false from this
        /// method will result in this round of Draw calls being skipped.
        /// </summary>
        /// <param name="gameTime"></param>
        /// <returns></returns>
        bool BeforeDraw() override {}

        /// <summary>
        /// When implemented in a derived class, causes the game to enter
        /// full-screen mode.
        /// </summary>
        void EnterFullScreen() override {}

        /// <summary>
        /// When implemented in a derived class, causes the game to exit
        /// full-screen mode.
        /// </summary>
        void ExitFullScreen() override {}

        /// <summary>
        /// Starts a device transition (windowed to full screen or vice versa).
        /// </summary>
        /// <param name='willBeFullScreen'>
        /// Specifies whether the device will be in full-screen mode upon completion of the change.
        /// </param>
        void BeginScreenDeviceChange  (
                    bool willBeFullScreen
        ) override {}

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
        ) override {}

        void Present() override { }

        void OnIsMouseVisibleChanged() override {}

        /// <summary>
        /// Called by the GraphicsDeviceManager to notify the platform
        /// that the presentation parameters have changed.
        /// </summary>
        /// <param name="pp">The new presentation parameters.</param>
        void OnPresentationChanged() override {}

        // /// <summary>
        // /// Log the specified Message.
        // /// </summary>
        // /// <param name='Message'>
        // /// 
        // /// </param>
        // [System.Diagnostics.Conditional("DEBUG")]
        void Log(char* Message) override {}		


        void Dispose() override {}
    };
}