#pragma once

#include "Utilities.h"
#include "Point.h"

class BMPLoader {

public:

    BMPLoader(const unsigned char* rawData, const unsigned int width, const unsigned int height);
   
    ~BMPLoader() = default;

    static BMPLoader loadFromFile(const char* fileName);

    utils::array<ColoredPoint2> getPoints() const;

private:

    BMPLoader(const unsigned int size);

private:

    utils::array<ColoredPoint2> data;

};
