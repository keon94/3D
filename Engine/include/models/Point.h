#pragma once

class Point2 {

private:
    unsigned x;
    unsigned y;

public:

    Point2() : x(0), y(0) {}
    
    constexpr Point2(const unsigned x, const unsigned y) : x(x), y(y) {}

    inline bool operator== (const Point2& other) {
        return x == other.x && y == other.y;
    }

    inline bool operator!= (const Point2& other) {
        return !(*this == other);
    }

    inline unsigned getX() const {
        return x;
    } 

    inline unsigned getY() const {
        return y;
    }

    inline void move(int deltaX, int deltaY) {
        x += deltaX;
        y += deltaY;
    }

};

#include "Colors.h"

struct ColoredPoint2 {
    Point2 point;
    Color color;
};