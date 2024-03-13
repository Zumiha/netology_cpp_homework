#pragma once
#include "0_Figure.h"

class Quadrilateral : public Figure {
public:
    Quadrilateral(int a, int b, int c, int d, int A, int B, int C, int D);

private:
    void setSides(int a, int b, int c, int d);

    void setAngles(int A, int B, int C, int D);

    const int* sideCntr() override;
    const int* angleCntr() override;

    int tetra = 4;
    int tetraSide[4] = {};
    int tetraAngle[4] = {};
};