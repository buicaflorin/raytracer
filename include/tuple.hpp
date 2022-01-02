#ifndef _TUPLE_HPP_
#define _TUPLE_HPP_

#include<cstdint>
#include<cmath> //sqrt
#include<cassert>

class Tuple{

    public:

    float x;
    float y;
    float z;
    uint32_t w; //1-point, 0-vector
    enum TUPLE_TYPE{
        VECTOR,
        POINT
    };

    Tuple();

    Tuple(uint32_t in_type);

    Tuple(float in_x, float in_y, float in_z, uint32_t in_type);

    Tuple operator + (const Tuple& b);

    Tuple operator - (const Tuple& b);

    Tuple operator ! ();

    float dot (Tuple& in);
    /*
    vector(a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x)
    The out vector is perpendicular on both input vectors*/
   Tuple cross(Tuple& in);

    Tuple operator * (float scalar);

    Tuple operator / (float scalar);

    bool operator == (Tuple& inTup);

    //vector magnitude using Pythagora's theorem
    float getMagnitude();

    Tuple getNormalized();

    void normalize(void);

    void print(void);
};

#endif