#include "commonmath.hpp"
#include "stdio.h"
#include<cmath>

bool RtMath::isEqual(float a, float b){
    if(std::abs(a - b) < RtMath::EPSILON){
        return true;
    }
    return false;
}