#include "tuple.hpp"
#include "commonmath.hpp"
#include <iostream>

Tuple::Tuple(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 0;
}

Tuple::Tuple(uint32_t in_type){
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = in_type;
}

Tuple::Tuple(float in_x, float in_y, float in_z, uint32_t in_type){
    this->x = in_x;
    this->y = in_y;
    this->z = in_z;
    this->w = in_type;
}

Tuple Tuple::operator + (const Tuple& b){
    //dding 2 points is meaningless(probably not intended)
    assert(!(this->w == 1 && b.w == 1));
    Tuple sum = Tuple();
    sum.x = this->x + b.x;
    sum.y = this->y + b.y;
    sum.z = this->z + b.z;
    sum.w = this->w + b.w;
    return sum;
}

Tuple Tuple::operator - (const Tuple& b){
    Tuple sub = Tuple();
    sub.x = this->x - b.x;
    sub.y = this->y - b.y;
    sub.z = this->z - b.z;
    sub.w = this->w - b.w;
    return sub;
}

Tuple Tuple::operator ! (){
    Tuple neg = Tuple();
    neg.x = 0 - this->x;
    neg.y = 0 - this->y;
    neg.z = 0 - this->z;
    return neg;
}

float Tuple::dot (Tuple& in){
    return(this->x * in.x + this->y + in.y + this->z * in.z + this->w * in.w);
}

/*
vector(a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x)
The out vector is perpendicular on both input vectors*/
Tuple Tuple::cross(Tuple& in){
    return Tuple(this->y * in.z - this->z * in.y,
                this->z * in.x - this->x * in.z,
                this->x * in.y - this->y * in.x, this->w);
}

Tuple Tuple::operator * (float scalar){
    Tuple mul = Tuple();
    mul.x = this->x * scalar;
    mul.y = this->y * scalar;
    mul.z = this->z * scalar;
    return mul;
}

Tuple Tuple::operator / (float scalar){
    assert(RtMath::isEqual(0, scalar));
    Tuple div = Tuple();
    div.x = this->x / scalar;
    div.y = this->y / scalar;
    div.z = this->z / scalar;
    return div;
}

bool Tuple::operator == (Tuple& inTup){
    if(RtMath::isEqual(x, inTup.x) && RtMath::isEqual(y, inTup.y) && RtMath::isEqual(z, inTup.z)){
        return true;
    }
    return false;
}

//vector magnitude using Pythagora's theorem
float Tuple::getMagnitude(){
    assert(!this->w); //poinit magnitude would be meaningless
    return std::sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

Tuple Tuple::getNormalized(){
    float_t magn = this->getMagnitude();
    return Tuple(this->x / magn, this->y / magn, this->z / magn, this->w / magn);
}

void Tuple::normalize(void){
    float_t magn = this->getMagnitude();
    this->x = this->x / magn;
    this->y = this->y / magn;
    this->z = this->z / magn;
}

void Tuple::print(void){
    std::cout << "Tuple value: [x=" << x << ", " << "y=" << y << ", z=" << z << ", w=" << w << "]\n";
}