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

    /*
    inline Point2 operator+ (const Point2& other) {
        return Point2(x + other.x, y + other.y); 
    }

    inline Point2 operator- (const Point2& other) {
        return Point2(x - other.x, y - other.y); 
    }

    inline Point2 operator* (const unsigned && scalar) {
        return Point2(scalar*x, scalar*y);
    }
    */

    inline unsigned  getX() const {
        return x;
    } 

    inline unsigned  getY() const {
        return y;
    }

    inline void move(int deltaX, int deltaY) {
        x += deltaX;
        y += deltaY;
    }

};