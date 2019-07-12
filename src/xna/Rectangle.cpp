#include "xna/Rectangle.h"

namespace xna {

    Rectangle::Rectangle() { }
    Rectangle::Rectangle(int x, int y, int width, int height) {
        X = x;
        Y = y;
        Width = width;
        Height = height;
    }

    Rectangle::~Rectangle() { }

    bool Rectangle::Contains(Rectangle* value) {
        return ((((X <= value->X) && 
            ((value->X + value->Width) <= (X + Width))) && 
            (Y <= value->Y)) && 
            ((value->Y + value->Height) <= (Y + Height)));

    }

}
