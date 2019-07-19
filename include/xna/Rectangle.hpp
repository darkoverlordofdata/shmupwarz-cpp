#pragma once

namespace xna {

    class Rectangle {
        
        public:
        int X;
        int Y;
        int Width;
        int Height; 
        Rectangle() { }
        Rectangle(int x, int y, int width, int height) {
            X = x;
            Y = y;
            Width = width;
            Height = height;
        }

        ~Rectangle() { }

        bool Contains(Rectangle* value) {
            return ((((X <= value->X) && 
                ((value->X + value->Width) <= (X + Width))) && 
                (Y <= value->Y)) && 
                ((value->Y + value->Height) <= (Y + Height)));

        }
    };

}
