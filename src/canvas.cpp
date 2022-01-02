#include "canvas.hpp"
#include<iostream>


Canvas::Canvas(uint32_t width, uint32_t height){
    this->width = width;
    this->height = height;
    this->pixelColors = new std::vector<Color>(width * height);
}

uint32_t Canvas::getWidth(void){
    return this->width;
}

uint32_t Canvas::getHeigth(void){
    return this->height;
}

Canvas::~Canvas(){
    delete this->pixelColors;
}

Color* Canvas::getPixelAt(uint32_t inX, uint32_t inY){
    if(inY < this->height && inX < this->width){
        return &(this->pixelColors->at(inX * inY));
    }
    else{
        std::cerr << "Requested pixel get is out of range\n";
        return &(this->pixelColors->at(this->width * this->height));
    }
}

bool Canvas::setPixelAt(uint32_t inX, uint32_t inY, Color& inColor){
    if((inY < this->height) && (inX < this->width)){
        this->pixelColors->at(inX + (this->height - inY) * this->height) = inColor;
        return true;
    }
    else{
        std::cerr << "Requested pixel set is out of range\n";
        return false;
    }
}