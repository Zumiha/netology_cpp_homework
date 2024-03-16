#pragma once
#include "0_Figure.h"

class Triangle : public Figure {
public:
    Triangle(int a, int b, int c, int A, int B, int C);

private:
    void setSides(int a, int b, int c);
    void setAngles(int A, int B, int C);

    const int* sideCntr() override;
    const int* angleCntr() override;

    int tri = 3;
    int triSide[3] = {};
    int triAngle[3] = {};
};
