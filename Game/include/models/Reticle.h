#pragma once
#include "models/Point.h"
#include "Colors.h"
#include "models/Drawable.h"
#include "Controllable.h"
#include "periph/Keyboard.h"

class Reticle : public Drawable, public Controllable<Keyboard> {

private:
    Point2 center;
    Color color;
    int velocity;

private:


public:

    // number of pixels from center to start of crosshair
    static constexpr int CrossHairsPx_Min = 5;
    // number of pixels from center to end of crosshair
    static constexpr int CrossHairsPx_Max = 10;

public:
    
    Reticle(const Point2& center, const Color& color) : center(center), color(color), velocity(1) {}

    void move(int deltaX, int deltaY);

    inline void setVelocity(const unsigned velocity) {
        this->velocity = velocity;
    }

    virtual void draw(Graphics& gfx) const override;

    virtual void control(Keyboard& kbd) override;

    inline Point2 getCenter() const {
        return center;
    } 
};
