#pragma once

namespace xna {

    class Rectangle {
        
    public:
        Rectangle();
        Rectangle(int x, int y, int width, int height);
        ~Rectangle();   

        bool Contains(Rectangle* value);

        int X;
        int Y;
        int Width;
        int Height; 
    };
}
