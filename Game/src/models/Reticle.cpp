#include "models/Reticle.h"
#include "utils/DrawUtilities.h"

void Reticle::draw(Graphics& gfx) const {
    
    DrawUtilities::draw(gfx, center, color);
    
    unsigned cx = center.getX();
    unsigned cy = center.getY();

    DrawUtilities::draw(gfx, Line(Point2(cx + CrossHairsPx_Min, cy), Point2(cx + CrossHairsPx_Max, cy)), color);
    DrawUtilities::draw(gfx, Line(Point2(cx - CrossHairsPx_Min, cy), Point2(cx - CrossHairsPx_Max, cy)), color);

    DrawUtilities::draw(gfx, Line(Point2(cx, cy + CrossHairsPx_Min), Point2(cx, cy + CrossHairsPx_Max)), color);
    DrawUtilities::draw(gfx, Line(Point2(cx, cy - CrossHairsPx_Min), Point2(cx, cy - CrossHairsPx_Max)), color);

}

void Reticle::control(Keyboard& kbd) {

    if(kbd.keyIsPressed(VK_UP))
        move(0, -velocity);
    if(kbd.keyIsPressed(VK_LEFT))
        move(-velocity, 0);
    if(kbd.keyIsPressed(VK_DOWN))
        move(0, velocity);
    if(kbd.keyIsPressed(VK_RIGHT))
        move(velocity, 0);
}

void Reticle::move(int deltaX, int deltaY) {
    int x = center.getX();
    int y = center.getY();

    if(x + CrossHairsPx_Max + deltaX > Graphics::ScreenWidth) { //possible if delta X > 0
        deltaX = Graphics::ScreenWidth - x - CrossHairsPx_Max ;
    }
    else if(x - CrossHairsPx_Max + deltaX < 0) { //possible if delta X < 0
        deltaX = CrossHairsPx_Max  - x;
    }
    
    if(y + CrossHairsPx_Max + deltaY > Graphics::ScreenHeight) {
        deltaY = Graphics::ScreenHeight - y - CrossHairsPx_Max ;
    }
    else if(y - CrossHairsPx_Max + deltaY < 0) {
        deltaY = CrossHairsPx_Max - y;
    }

    center.move(deltaX, deltaY);
}