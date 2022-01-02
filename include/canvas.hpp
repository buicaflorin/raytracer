#include<stdio.h>
#include <stdint.h>
#include "color.hpp"
#include <vector>

class Canvas{
    uint32_t width;
    uint32_t height;

    public:
    std::vector<Color>* pixelColors;
    Canvas(uint32_t width, uint32_t height);

    ~Canvas();

    uint32_t getWidth(void);
    uint32_t getHeigth(void);
    Color* getPixelAt(uint32_t inX, uint32_t inY);

    bool setPixelAt(uint32_t inX, uint32_t inY, Color& inColor);
};