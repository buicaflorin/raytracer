#include<stdio.h>
#include<iostream>
#include<cassert>
#include<cstdint>
#include<cmath> //sqrt
#include "renderer.hpp"
#include<memory>
#include<vector>
#include "tuple.hpp"
#include "commonmath.hpp"
#include "matrix.hpp"

//=================================================
struct Projectile{
    Projectile(Tuple& inPos, Tuple& inVel){
        this->position = inPos;
        this->velocity = inVel;
    }
    Projectile(){
        ;
    }
    //a point with a vector
    Tuple position;
    Tuple velocity;
};

struct Environment{
    Environment(){
        ;
    }
    Environment(Tuple& inGrav, Tuple& inWind){
        this->gravity = inGrav;
        this->wind = inWind;
    }
    //two vectors
    Tuple gravity;
    Tuple wind;
};

void tick(Projectile& prevProj, Environment& env, Projectile& nextProj){
    nextProj.position = prevProj.position + prevProj.velocity;
    nextProj.velocity = prevProj.velocity + env.gravity + env.wind;
} 

void testProjectile(Renderer* pRenderer){
    Tuple projPos(200, 200, 0, 1);
    Tuple projVelo(1.5, 1.5, 0, 0);
    projVelo.normalize();
    Projectile currProj(projPos, projVelo);
    Color projColor(220,0,0);

    Tuple envGrav(0, -0.1, 0, 0);
    Tuple envWind(0.2, 0, 0, 0);
    Environment env(envGrav, envWind);
    Projectile nextProj;
    while(currProj.position.y >= 0.0 && currProj.position.x < 640){
        std::cout << "==>running tick. pos.x=" << currProj.position.x << " pos.y=" << currProj.position.y << " pos.z=" << currProj.position.z <<"\n";
        tick(currProj, env, nextProj);
        if(false == pRenderer->setPixelAt(currProj.position.x, currProj.position.y, projColor)){
            break;
        }
        pRenderer->render();
        SDL_Delay(100);
        currProj.position = nextProj.position;
        currProj.velocity = nextProj.velocity;
    }
    pRenderer->saveWindow("./myprojectyle.bmp");
}

//=====================
void TEST(void){
    float a = 11.22;
    float b = 11.23;

    bool iseq = RtMath::isEqual(a,b);
    std::cout << "the numbers are not equal:" << iseq << "\n";

    iseq = RtMath::isEqual(21.222222, 21.222222);
    std::cout << "the numbers are equal:" << iseq << "\n";

    Tuple testTuple1 = Tuple(-3.1, 2.0, 11.4, 0);
    Tuple testTuple2 = Tuple(-3.1, 2.0, 11.4, 1);

    Tuple testTuple3 = testTuple1 + testTuple2;
    std::cout << "tuples sum type:" << testTuple3.w << " x:" << testTuple3.x << " y:" << testTuple3.y << " z:" << testTuple3.z << "\n";

    testTuple3 = testTuple1 - testTuple2;
    std::cout << "tuples sub type:" << testTuple3.w << " x:" << testTuple3.x << " y:" << testTuple3.y << " z:" << testTuple3.z << "\n";

    Tuple testTuple4 = !testTuple1;
    std::cout << "tuple1 negated type:" << testTuple4.w << " x:" << testTuple4.x << " y:" << testTuple4.y << " z:" << testTuple4.z << "\n";

    Tuple tmagn = Tuple(1,2,3,0);
    std::cout << "tuple magnitudes is:" << tmagn.getMagnitude() << " expected: " << std::sqrt(14) << "\n";
    assert(RtMath::isEqual(std::sqrt(14), tmagn.getMagnitude()));

    Tuple tmagn2 = Tuple(2,-1,3,0);
    std::cout << "tuple magnitudes is:" << tmagn2.getMagnitude() << " expected: " << std::sqrt(14) << "\n";
    assert(RtMath::isEqual(sqrt(14), tmagn2.getMagnitude()));

    Matrix::data_t inMat_1234 = {{1,2,3,4}, {5,6,7,8}, {9,8,7,6}, {5,4,3,2}};
    Matrix::data_t inMat_rand = {{-2,1,2,3}, {3,2,1,-1}, {4,3,6,5}, {1,2,7,8}};
    Matrix::data_t out123x_expected = {{20,22,50,48}, {44,54,114,108},{40,58,110,102}, {16,26,46,42}};

    Matrix::data_t inMat_0 = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};
    //identity matrix
    Matrix::data_t inMat_d1 = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
    Matrix::data_t inMat_1 = {{1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}};

    Matrix testMat_d1(inMat_d1);
    Matrix testMat_1(inMat_1);
    Matrix testMat_1234(inMat_1234);
    Matrix testMat_rand(inMat_rand);

    Matrix mulMat = testMat_1 * testMat_d1;

    testMat_d1.print();
    testMat_1.print();
    mulMat.print();
    std::cout << "zeroed mat:\n";
    mulMat.fill(0.0);
    mulMat.print();

    Matrix mulMat_2 = testMat_1234 * testMat_d1;
    std::cout << "1234 mat:\n";
    mulMat_2.print();
    if(!(mulMat_2 == testMat_1234)){
        assert(1);
    }
    if(mulMat_2 != testMat_1234){
        assert(1);
    }

    Matrix out123xrandExpect = Matrix(out123x_expected);
    Matrix out123xrandMult = testMat_1234 * testMat_rand;
    out123xrandMult.print();
    if(out123xrandMult != out123xrandExpect){
        assert(1);
    }

    //transpose
    Matrix testTranspose_1234(inMat_1234);
    testTranspose_1234.transpose();
    std::cout << "Matrix {{1,2,3,4}, {5,6,7,8}, {9,8,7,6}, {5,4,3,2}} transposed:\n";
    testTranspose_1234.print();
   //TODO assert

   //submatrix
   std::cout << "submatrix {{6,7,8}, {8,7,6}, {4,3,2}} \n";
   Matrix subMat = testMat_1234.getSubmatrix(0,0);
   Matrix::data_t subMat_ExpectData = {{6,7,8}, {8,7,6}, {4,3,2}};
   Matrix subMat_Expected(subMat_ExpectData);
   subMat.print();
   if(subMat_Expected != subMat){
       assert(0);
   }

    Matrix subMat_11 = testMat_1234.getSubmatrix(1,1);
    Matrix::data_t subMat11_ExpectData = {{1,3,4}, {9,7,6}, {5,3,2}};
    std::cout << "submatrix expected: {{1,3,4}, {9,7,6}, {5,3,2}} Actual:\n";
    subMat_11.print();
    //assert
   //Matrix::data_t inMat_1234 = {{1,2,3,4}, {5,6,7,8}, {9,8,7,6}, {5,4,3,2}};
    
   //minor
   Matrix::data_t minorMat_Data = {{6,7,8}, {8,7,6}, {4,3,2}};
   Matrix minorMat(minorMat_Data);
   /*should be equal to det |6 8|
                            |4 2|
    */
   auto resMinor = minorMat.getMinor(1, 1);
   auto resDet = 6 * 2 - 8 * 4;
   std::cout << "Minor result:" << resMinor << " expected:" << resDet << "\n";
   assert(RtMath::isEqual(resDet, resMinor));


}

void testDet(void){
    /* 
    D =  | 1 | 2 | 6 |
         | -5 | 8 | -4 |
         | 2 | 6 | 4 |
         det(D) = -196
    */ 
    Matrix::data_t data = {{1,2,6}, {-5,8,-4}, {2,6,4}};
    auto det = Matrix(data).getDet(0,0);
    std::cout << "Det:" << det << " expected = -196\n";
}

void testInvertible(void){
    Matrix::data_t noninvert = {{20,22,50,48}, {44,54,114,108},{40,58,110,102}, {0,0,0,0}};
    Matrix::data_t invert = {{6,4,4,4}, {5,5,7,6},{4,-9,3,-7}, {9,1,7,-6}};

    auto mNonInvert = Matrix(noninvert);
    bool isInvert = mNonInvert.isInvertible();
    assert(false == isInvert);

    auto mInvert = Matrix(invert);
    isInvert = mInvert.isInvertible();
    assert(true == isInvert);

    float det = mInvert.getDet(0,0);
    std::cout << "Determinant value:" << det << " expected: -2120\n";
}

void testInverse(void){
    /*
    Given the following 4x4 matrix A:
    | 8 | -5 | 9 | 2 |
    | 7 | 5 | 6 | 1 |
    | -6 | 0 | 9 | 6 |
    | -3 | 0 | -9 | -4 |
    Then inverse(A) is the following 4x4 matrix:
    | -0.15385 | -0.15385 | -0.28205 | -0.53846 |
    | -0.07692 | 0.12308 | 0.02564 | 0.03077 |
    | 0.35897 | 0.35897 | 0.43590 | 0.92308 |
    | -0.69231 | -0.69231 | -0.76923 | -1.92308 |
    */
    Matrix::data_t origData = {{8,-5,9,2}, {7,5,6,1},{-6,0,9,6}, {-3,0,-9,-4}};
    Matrix::data_t inverseData = {
    { -0.15385, -0.15385, -0.28205, -0.53846 },
    { -0.07692, 0.12308, 0.02564, 0.03077 },
    { 0.35897, 0.35897, 0.43590, 0.92308 },
    { -0.69231, -0.69231, -0.76923, -1.92308 }};

    Matrix mOrig = Matrix(origData);
    Matrix mInverse = mOrig.getInverse();
    std::cout << "Test inverse:\n";
    mInverse.print();
    Matrix mInverseExpect = Matrix(inverseData);
    assert(mInverse == mInverseExpect);

    //test data 2
    Matrix::data_t origData_2 = {
        { 9 , 3 , 0 , 9 },
        { -5 , -2 , -6 , -3 },
        { -4 , 9 , 6 , 4 },
        { -7 , 6 , 6 , 2 }};
    Matrix::data_t inverseData_2 = {
        { -0.04074, -0.07778 , 0.14444, -0.22222 },
        { -0.07778 , 0.03333, 0.36667, -0.33333 },
        { -0.02901 , -0.14630, -0.10926 , 0.12963},
        { 0.17778 , 0.06667 , -0.26667 , 0.33333 }};
    Matrix mOrig_2(origData_2);
    Matrix mInverse_2_Expect(inverseData_2);

    Matrix minVerseCalc = mOrig_2.getInverse();
    minVerseCalc.print();
    assert(minVerseCalc == mInverse_2_Expect);
}

void testTranslation(void){
    Matrix translation(4,4, 0.0);
    Tuple inTup(5, -3, 2, 1);
    Matrix translated = translation.getTranslation(inTup);
    std::cout << "Translation matrix(5,-3,2)\n";
    translated.print();
    Tuple point = Tuple(-3, 4, 5, 1);
    std::cout << "Point:\n";
    point.print();
    Tuple translatedTup = translated * point;
    translatedTup.print();

    Tuple expectedTr(2,1,7,1);
    assert(translatedTup == expectedTr);

    //multiply by the inverse of the translation matrix
    //should translate in opposite direction
    Matrix invTr = translated.getInverse();
    Tuple pTransfInv = invTr * point;
    Tuple expectedInvTr(-8,7,3,1);
    assert(pTransfInv == expectedInvTr);

    //translation should not affect vectors
    Tuple vector = Tuple(-3, 4, 5, 0);
    Tuple transfVect = translated * vector;
    assert(vector == transfVect);
}

void testScaling(void){
    Tuple scaling(2, 3, 4, 1);
    Matrix scalingTransform = Matrix::getScaling(scaling);
    Matrix invScalingTransform = scalingTransform.getInverse();
    Tuple toScale(-4, 6, 8, 0);
    Tuple invVect = invScalingTransform * toScale;
    Tuple expectVect(-2, 2, 2, 0);
    assert(expectVect == invVect);
    std::cout << "scaled vector\n";
    expectVect.print();
}
//=========================


int main(int argc, char* argv[]){
    TEST();
    testDet();
    testInvertible();
    testInverse();
    // Renderer* pRenderer = new Renderer();

    testTranslation();
    testScaling();
    // pRenderer->startRunning();
    // while (pRenderer->isRunning()){
    //     /* code */
    //     testProjectile(pRenderer);

    //     pRenderer->render();
    //     pRenderer->handleEvents();
    //     pRenderer->stopRunning();
    // }

    return 0;
}

