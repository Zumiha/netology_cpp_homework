#include "02.0_quadri.h"

Quadrilateral::Quadrilateral(int a, int b, int c, int d, int A, int B, int C, int D):Figure(tetra) {
    setSides(a, b, c, d);
    setAngles(A, B, C, D);

    setShape(tetra);

    setName("Четырехугольник");
}


void Quadrilateral::setSides(int a, int b, int c, int d) {
    this->tetraSide[0] = a;
    this->tetraSide[1] = b;
    this->tetraSide[2] = c;
    this->tetraSide[3] = d;
}

void Quadrilateral::setAngles(int A, int B, int C, int D) {
    this->tetraAngle[0] = A;
    this->tetraAngle[1] = B;
    this->tetraAngle[2] = C;
    this->tetraAngle[3] = D;
}

const int* Quadrilateral::sideCntr() {
    return this->tetraSide;
}

const int* Quadrilateral::angleCntr() {
    return this->tetraAngle;
}

int tetra = 4;
int tetraSide[4] = {};
int tetraAngle[4] = {};