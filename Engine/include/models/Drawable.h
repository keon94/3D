#pragma once

#include "Graphics.h"

class Drawable {

public:

    virtual ~Drawable() {};
    virtual void draw(Graphics& gfx) const = 0; 

};
