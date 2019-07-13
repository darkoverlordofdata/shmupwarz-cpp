#include "xna/GamePlatform.h"
#include "xna/SDL/SDLGamePlatform.h"

namespace xna {

    GamePlatform::GamePlatform() { }
    GamePlatform::GamePlatform(Game* game) { 
        mGame = game;
    }

    GamePlatform::~GamePlatform() {
    }

    bool GamePlatform::InFullScreenMode() {
        return mInFullScreenMode;
    }
    GamePlatform* GamePlatform::PlatformCreate(Game* game) {
        
        return new SDLGamePlatform(game);
    }

    GameRunBehavior GamePlatform::DefaultRunBehavior() {};

    bool GamePlatform::IsActive() {
        return mIsActive;
    }

    void GamePlatform::IsActive(bool value) {
        if (mIsActive != value) {
            mIsActive = value;
            // EventHelpers.Raise()
        }
    }

    bool GamePlatform::IsMouseActive() {
        return mIsMouseActive;
    }

    void GamePlatform::IsMouseActive(bool value) {
        if (mIsMouseActive != value) {
            mIsMouseActive = value;
            // OnIsMouseVisibleChanged();
        }
    }

    GameWindow* GamePlatform::Window() {
        return mWindow;
    }

    void GamePlatform::Window(GameWindow* value) {
        if (mWindow != nullptr) {
            mWindow = value;
        }
    }

    /// <summary>
    /// Raises the AsyncRunLoopEnded event.  This method must be called by
    /// derived classes when the asynchronous run loop they start has
    /// stopped running.
    /// </summary>
    void GamePlatform::RaiseAsyncRunLoopEnded() {
        // EventHelpers.Raise();
    }

    /// <summary>
    /// Gives derived classes an opportunity to do work before any
    /// components are initialized.  Note that the base implementation sets
    /// IsActive to true, so derived classes should either call the base
    /// implementation or set IsActive to true by their own means.
    /// </summary>
    void GamePlatform::BeforeInitialize() {
        mIsActive = true;
    }

    /// <summary>
    /// Gives derived classes an opportunity to do work just before the
    /// run loop is begun.  Implementations may also return false to prevent
    /// the run loop from starting.
    /// </summary>
    /// <returns></returns>
    bool GamePlatform::BeforeRun() {
        return true;
    }

    /// <summary>
    /// When implemented in a derived, ends the active run loop.
    /// </summary>
    void GamePlatform::Exit() {}

    /// <summary>
    /// When implemented in a derived, starts the run loop and blocks
    /// until it has ended.
    /// </summary>
    void GamePlatform::RunLoop() {}

    /// <summary>
    /// When implemented in a derived, runs the loop one time
    /// until it has ended.
    /// </summary>
    void GamePlatform::RunOnce() {}

    /// <summary>
    /// When implemented in a derived, starts the run loop and returns
    /// immediately.
    /// </summary>
    void GamePlatform::StartRunLoop() {}

    /// <summary>
    /// Gives derived classes an opportunity to do work just before Update
    /// is called for all IUpdatable components.  Returning false from this
    /// method will result in this round of Update calls being skipped.
    /// </summary>
    /// <param name="gameTime"></param>
    /// <returns></returns>
    bool GamePlatform::BeforeUpdate() {}

    /// <summary>
    /// Gives derived classes an opportunity to do work just before Draw
    /// is called for all IDrawable components.  Returning false from this
    /// method will result in this round of Draw calls being skipped.
    /// </summary>
    /// <param name="gameTime"></param>
    /// <returns></returns>
    bool GamePlatform::BeforeDraw() {}

    /// <summary>
    /// When implemented in a derived class, causes the game to enter
    /// full-screen mode.
    /// </summary>
    void GamePlatform::EnterFullScreen() {}

    /// <summary>
    /// When implemented in a derived class, causes the game to exit
    /// full-screen mode.
    /// </summary>
    void GamePlatform::ExitFullScreen() {}

    /// <summary>
    /// Starts a device transition (windowed to full screen or vice versa).
    /// </summary>
    /// <param name='willBeFullScreen'>
    /// Specifies whether the device will be in full-screen mode upon completion of the change.
    /// </param>
    void GamePlatform::BeginScreenDeviceChange (
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
    void GamePlatform::EndScreenDeviceChange (
                char* screenDeviceName,
                int clientX,
                int clientY,
                int clientWidth,
                int clientHeight
    ) {}

    void GamePlatform::Present() { }

    void GamePlatform::OnIsMouseVisibleChanged() {}

    /// <summary>
    /// Called by the GraphicsDeviceManager to notify the platform
    /// that the presentation parameters have changed.
    /// </summary>
    /// <param name="pp">The new presentation parameters.</param>
    void GamePlatform::OnPresentationChanged() {}

    // /// <summary>
    // /// Log the specified Message.
    // /// </summary>
    // /// <param name='Message'>
    // /// 
    // /// </param>
    // [System.Diagnostics.Conditional("DEBUG")]
    void GamePlatform::Log(char* Message) {}		

}