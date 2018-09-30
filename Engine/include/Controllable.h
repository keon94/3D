#pragma once

template <typename I>
class Controllable {

public:

    virtual ~Controllable() {};

    virtual void control(I& input) = 0;

};