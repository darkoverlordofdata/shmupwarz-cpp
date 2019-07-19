#pragma once

namespace xna {

    class GraphicsDeviceManager {
        
    public:
    const static int DefaultWindowPositionX = 0;
    const static int DefaultWindowPositionY = 0;
    const static int DefaultBackBufferWidth = 800;
    const static int DefaultBackBufferHeight = 480;

    GraphicsDeviceManager() { }
    
    ~GraphicsDeviceManager() { }

    };
}