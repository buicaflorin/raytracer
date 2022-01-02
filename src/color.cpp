#include "color.hpp"


Color::Color(){
    this->red = 0;
    this->green = 0;
    this->blue = 0;
}
Color::Color(float r, float g, float b){
    this->red = r;
    this->green = g;
    this->blue = b;
}

Color Color::operator + (float scalar){
    Color mul = Color();
    mul.red = this->red + scalar;
    mul.green = this->green + scalar;
    mul.blue = this->blue + scalar;
    return mul;
}

Color Color::operator - (float scalar){
    Color mul = Color();
    mul.red = this->red - scalar;
    mul.green = this->green - scalar;
    mul.blue = this->blue - scalar;
    return mul;
}

Color Color::operator * (float scalar){
    Color mul = Color();
    mul.red = this->red * scalar;
    mul.green = this->green * scalar;
    mul.blue = this->blue * scalar;
    return mul;
}

//blend colors using Haramard product
Color Color::operator * (Color& inColor){
    Color blend = Color();
    blend.red = this->red * inColor.red;
    blend.green = this->green * inColor.green;
    blend.blue = this->blue * inColor.blue;
    return blend;
}

void Color::operator = (Color& inColor){
    this->red = inColor.red;
    this->green = inColor.green;
    this->blue = inColor.blue;
}

Color::~Color(){
    ;
}
