#include "xna/Rectangle.h"

namespace xna {

    Rectangle::Rectangle() { }
    Rectangle::Rectangle(int x, int y, int width, int height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    Rectangle::~Rectangle() { }

    bool Rectangle::Contains(Rectangle* value) {
        return ((((this->x <= value->x) && 
            ((value->x + value->width) <= (this->x + this->width))) && 
            (this->y <= value->y)) && 
            ((value->y + value->height) <= (this->y + this->height)));

    }

}
