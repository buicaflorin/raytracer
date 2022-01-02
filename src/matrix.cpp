#include "matrix.hpp"
#include<iostream>
#include "commonmath.hpp"

Matrix::Matrix(data_t& inMat)
{
    this->data = inMat;
    this->size = inMat.size() * inMat[0].size();
}

Matrix::Matrix(uint32_t lines, uint32_t cols, float values)
{
    this->data = data_t(lines, std::vector<float>(cols));
    this->fill(values);
}

void Matrix::fill(float value){
    for(auto line = 0; line < data.size(); line++){
        std::fill(data[line].begin(), data[line].end(), value);
    }
}

void Matrix::print(void){
    for(auto line : data){
        for(auto col : line){
            std::cout << col << " ";
        }
        std::cout << "\n";
    }
}

uint32_t Matrix::getSize(void){
    return this->size;
}

void Matrix::operator = (Matrix& inMat){
    if(inMat.data.size() == this->data.size()){
        for(auto line = 0; line < inMat.data.size(); line++){
            for(auto col = 0; col < inMat.data[line].size(); col++){
                this->data[line][col] = inMat.data[line][col];
            }
        }
    }
    else{
        std::cerr << "Failed to assign matrix due to different size.\n" <<__FUNCTION__;
    }
}

bool Matrix::operator == (Matrix& inMat){
    for(auto line = 0; line < inMat.data.size(); line++){
        for(auto col = 0; col < inMat.data[line].size(); col++){
            if(false == RtMath::isEqual(this->data[line][col], inMat.data[line][col])){
                return false;
            }
        }
    }
    return true;
}

void Matrix::transpose(void){
    //create with appropriate [col,row] size
    Matrix tr = Matrix(data[0].size(), data.size(), 0.0);
    for(auto line = 0; line < data.size(); line++){
        for(auto col = 0; col < data[0].size(); col++){
            tr.data[col][line] = data[line][col];
        }
    }
    *this = tr;
}

bool Matrix::operator != (Matrix& inMat){
    if(*this == inMat){
        return false;
    }
    return true;
}

/*
matrixMultiply(A, B):
Assume dimension of A is (m x n), dimension of B is (p x q)
Begin
   if n is not same as p, then exit
   otherwise define C matrix as (m x q)
   for i in range 0 to m - 1, do
      for j in range 0 to q – 1, do
         for k in range 0 to p, do
            C[i, j] = C[i, j] + (A[i, k] * B[k, j])
         done
      done
   done
End
*/
Matrix Matrix::operator * (Matrix& inMat){
    Matrix outMat(data.size(), inMat.data[0].size(), 0.0);
    if(data[0].size() == inMat.data.size()){
        for(auto line = 0; line < data.size(); line++){
            for(auto col = 0; col < inMat.data[0].size(); col++){
                for(auto k = 0; k < inMat.data.size(); k++){
                    outMat.data[line][col] += data[line][k] * inMat.data[k][col];
                }
            }
        }
        return outMat;
    }
    else{
        std::cerr << "Failed to multiply matrix due to unsupported size.\n" <<__FUNCTION__;
        return outMat;
    }
}

Tuple Matrix::operator * (Tuple& inTup){
    assert(data.size() == data[0].size() && data.size() == 4);
    //multiply column matrix tuple with 4x4 matrix to obrain translated tuple 
    Tuple outTup = Tuple();
    outTup.x = data[0][0] * inTup.x + data[0][1] * inTup.y + data[0][2] * inTup.z + data[0][3] * inTup.w;
    outTup.y = data[1][0] * inTup.x + data[1][1] * inTup.y + data[1][2] * inTup.z + data[1][3] * inTup.w;
    outTup.z = data[2][0] * inTup.x + data[2][1] * inTup.y + data[2][2] * inTup.z + data[2][3] * inTup.w;
    outTup.w = data[3][0] * inTup.x + data[3][1] * inTup.y + data[3][2] * inTup.z + data[3][3] * inTup.w;

    return outTup;
}

/*
Determinant for a 2x2 sub-matrix starting at given coordinates
det(0,0) for    |a b c| = a * e - b * d
                |d e f|
*/
float Matrix::getDet2x2(uint32_t inX, uint32_t inY){
    float det = 0.0;
    if((inX < data.size() - 1) && (inY < data[0].size() - 1)){
        det = (data[inX][inY] * data[inX + 1][inY + 1]) - (data[inX][inY + 1] * data[inX +1][inY]);
    }
    else{
        std::cerr << "Failed to calculate det due to unsupported size.\n" <<__FUNCTION__;
    }
    return det;
}

float Matrix::getDet(uint32_t inX, uint32_t inY){
    float det = 0.0;
    if((inX < data.size()) && inY < data[0].size()){
        //2x2 matrix
        if(data.size() == 2){
            det = (data[inX][inY] * data[inX + 1][inY + 1]) - (data[inX][inY + 1] * data[inX +1][inY]);
        }
        else{
            for(auto col = 0; col < data[0].size(); col++){
                det += data[0][col] * getCofactor(0,col);
            }
        }
    }
    else{
        std::cerr << "Failed to calculate det due to unsupported size.\n" <<__FUNCTION__;
    }
    return det;
}

//returns a submatrix by removing the given line and column
Matrix Matrix::getSubmatrix(uint32_t inX, uint32_t inY){
    auto subMatLines = data.size() - 1;
    auto subMatCols = data[0].size() - 1;
    Matrix submat(subMatLines, subMatCols, 0.0);

    auto destLine = 0;
    auto destCol = 0;

    //skip requested line and column
    for(auto origLine = 0; origLine < data.size(); origLine++){
        if(origLine == inX){
            continue;
        }
        destCol = 0;
        for(auto origCol = 0; origCol < data[0].size(); origCol++){
            if(origCol == inY){
                continue;
            }
            submat.data[destLine][destCol] = data[origLine][origCol];
            destCol++;
        }
        destLine++;
    }
    return submat;
}

//the minor at x,y is the determinant of the submatrix at x,y
float Matrix::getMinor(uint32_t inX, uint32_t inY){
    return this->getSubmatrix(inX, inY).getDet(0,0);
}

//calculates the minor at the given coordinates and applyes negative sign if (row+col)%2 !=0
float Matrix::getCofactor(uint32_t inX, uint32_t inY){
    Matrix submat = this->getSubmatrix(inX, inY);
    float minor = submat.getDet(0, 0);
    if((inX + inY) % 2 != 0){
        minor = 0 - minor;
    }
    return minor;
}

//matrix is invertible if its determinant is 0
bool Matrix::isInvertible(void){
    return (RtMath::isEqual(0, getDet(0,0)) ? false : true); 
}

Matrix Matrix::getInverse(void){
    //zero folled matrix of same size
    Matrix inverse = Matrix(data.size(), data[0].size(), 0.0);
    float det = getDet(0,0);
    for(auto line = 0; line < data.size(); line++){
        for(auto col = 0; col < data[0].size(); col++){
            float cofactor = getCofactor(line,col);
            inverse.data[col][line] = cofactor / det;
        }
    }
    return inverse;
}

Matrix Matrix::getTranslation(Tuple& inTup){
    Matrix::data_t tMat = {{1, 0, 0, inTup.x}, {0, 1, 0, inTup.y}, {0, 0, 1, inTup.z}, {0, 0, 0, inTup.w}};
    return Matrix(tMat);
}

Matrix Matrix::getScaling(Tuple& inTup){
    Matrix::data_t sMat = {{inTup.x, 0, 0, 0}, {0, inTup.y, 0, 0}, {0, 0, inTup.z, 0}, {0, 0, 0, inTup.w}};
    return Matrix(sMat);
}

Matrix::~Matrix()
{
    //no heap data used
}
