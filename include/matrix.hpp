#include<cstdint>
#include <vector>
#include "tuple.hpp"

class Matrix
{

public:
    using data_t =  std::vector<std::vector<float>>;
    Matrix(data_t& inMat);
    Matrix(uint32_t lines, uint32_t cols, float values);
    uint32_t getSize(void);
    void fill(float value);
    void operator = (Matrix& inMat);
    bool operator == (Matrix& inMat);
    bool operator != (Matrix& inMat);
    Matrix operator * (Matrix& inMat);
    void transpose(void);
    //returns a submatrix by removing the given line and column
    Matrix getSubmatrix(uint32_t inX, uint32_t inY);
    //calculates determinant from given coordinates for 2x2 matrix
    //the minor at x,y is the determinant of the submatrix at x,y
    float getMinor(uint32_t inX, uint32_t inY);
    float getCofactor(uint32_t inX, uint32_t inY);
    //calculates 2x2 det
    float getDet2x2(uint32_t inX, uint32_t inY);
    //calculates deter
    float getDet(uint32_t inX, uint32_t inY);
    bool isInvertible(void);
    //this operation assumes the matrix has been verified for invertibility
    Matrix getInverse(void);
    //returns 4x4 translation matrix
    static Matrix getTranslation(Tuple& inTup);
    //returns 4x4 scaling matrix
    static Matrix getScaling(Tuple& inTup);
    //multiplication by point/vactor
    Tuple operator * (Tuple& inTup);

    void print(void);
    ~Matrix();

    private:
    /* data */
    data_t data;
    uint32_t size;

};