#include "01.0_triangle.h"

Triangle::Triangle(int a, int b, int c, int A, int B, int C):Figure(tri) {
    setSides(a, b, c);
    setAngles(A, B, C);

    setShape(tri);

    setName("Треугольник");
}


void Triangle::setSides(int a, int b, int c) {
    this->triSide[0] = a;
    this->triSide[1] = b;
    this->triSide[2] = c;
}

void Triangle::setAngles(int A, int B, int C) {
    this->triAngle[0] = A;
    this->triAngle[1] = B;
    this->triAngle[2] = C;
}

const int* Triangle::sideCntr() {
    return this->triSide;
}

const int* Triangle::angleCntr() {
    return this->triAngle;
}

int tri = 3;
int triSide[3] = {};
int triAngle[3] = {};
