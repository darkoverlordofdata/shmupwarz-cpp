#pragma once

namespace xna {

    class Point {
        
    public:
        Point();
        Point(int x, int y);
        ~Point();    

        int X;
        int Y;
    };
}