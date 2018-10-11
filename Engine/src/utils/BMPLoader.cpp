#include "BMPLoader.h"
#include <utility>
#include <stdio.h>
#include <exception>

BMPLoader::BMPLoader(const unsigned int size) : data({ new ColoredPoint2[size], size }) {}

BMPLoader::BMPLoader(const unsigned char* rawData, const unsigned int width, const unsigned int height) : BMPLoader(width * height) {
    for (unsigned int i = 0, j = 0, x = 0, y = 0; i < this->data.size; ++i, j += 3) {
        this->data.data[i] = { Point2(x, y), Colors::makeRGB(rawData[j + 2], rawData[j + 1], rawData[j]) };
        y += x == width ? 1 : 0;
        x = x == width ? 0 : x + 1;
    }
}

BMPLoader BMPLoader::loadFromFile(const char* fileName) {

    FILE* bmpFile = nullptr;
    fopen_s(&bmpFile, fileName, "rb");

    int width = 0, height = 0;
    unsigned char* raw_data = nullptr;
    
    try {
        unsigned char info[54];
        fread(info, sizeof(unsigned char), 54, bmpFile); // read the 54-byte header

        // extract image height and width from header
        width = *(int*)&info[18];
        height = *(int*)&info[22];

        const int size = width * height;
        raw_data = new unsigned char[3 * size]; // allocate 3 bytes per pixel
        fread(raw_data, sizeof(unsigned char), 3 * size, bmpFile); // read the rest of the data at once
        fclose(bmpFile);
        bmpFile = nullptr;        
    }
    catch (const std::exception&) {
        if(bmpFile)
            fclose(bmpFile);
    } 
    if (!raw_data) {
        //TODO: Need to handle this
    }
    return std::move(BMPLoader(raw_data, width, height));
}

utils::array<ColoredPoint2> BMPLoader::getPoints() const {
    return this->data;
}