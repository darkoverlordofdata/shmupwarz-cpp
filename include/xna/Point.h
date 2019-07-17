#pragma once

namespace xna {

    class Point {

        public:
        int X;
        int Y;

        Point() { }
        Point(int x, int y) { 
            X = x;
            Y = y;
        }
        ~Point() { }

    };
}

