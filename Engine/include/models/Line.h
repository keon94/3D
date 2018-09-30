#pragma once

#include "Point.h"

class Line {

private:
    Point2 p1;
    Point2 p2;
public:
    Line(const Point2& p1, const Point2& p2) {
        if(p1.getX() > p2.getX()) {
            this->p1 = p2;
            this->p2 = p1;
        }   
        else {
            this->p1 = p1;
            this->p2 = p2;
        }
    }

    Point2 getLeftPoint() const {
        return p1;
    }

    Point2 getRightPoint() const {
        return p2;
    }

    void move(const int deltaX, const int deltaY) {
        p1.move(deltaX, deltaY);
        p2.move(deltaX, deltaY);
    }
};