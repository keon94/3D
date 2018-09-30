#pragma once

#include "Graphics.h"
#include "models/Line.h"

/**
 * namespace containing functions for drawing basic things
 */
namespace DrawUtilities {

    inline void draw(Graphics& gfx, const Point2& p, const Color& color) {
        gfx.putPixel(p.getX(), p.getY(), color);
    }

    void draw(Graphics& gfx, const Line& l, const Color& color) {

        const Point2 lpt = l.getLeftPoint();
        const Point2 rpt = l.getRightPoint();
        
        const int deltaX = rpt.getX() - lpt.getX();
        const int deltaY = rpt.getY() - lpt.getY();

        //unsigned absX = lpt.getX();
        //unsigned absY = lpt.getY();

        const bool x_oriented = deltaX*deltaX >= deltaY*deltaY;

        //X1: lpt dim1 beginning val, X2: lpt dim2 beginning value,  X1end: dim1 last val
        auto drawLine = [&x_oriented, &gfx, &color](unsigned X1, unsigned X2, const int delta, unsigned X1end) {
            int x2 = 0; //delta increments
            for(; X1 < X1end; ++X1) {
                gfx.putPixel(x_oriented*X1 + !x_oriented*X2, x_oriented*X2 + !x_oriented*X1, color);
                x2 = (x2 == delta) * delta; //0 or deltaY
                X2 += (x2 != 0) * x2;
            }
        };

        if(x_oriented) {
            drawLine(lpt.getX(), lpt.getY(), deltaY, rpt.getX()); 
        }
        else if(lpt.getY() < rpt.getY()){
            drawLine(lpt.getY(), lpt.getX(), deltaX, rpt.getY()); 
        }
        else {
            drawLine(rpt.getY(), lpt.getX(), deltaX, lpt.getY()); 
        }
    }
}