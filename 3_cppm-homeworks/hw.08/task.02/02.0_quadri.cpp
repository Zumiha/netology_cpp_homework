#include "02.0_quadri.h"
#include "ValError.h"
#include <iostream>
#include <sstream>

Quadrilateral::Quadrilateral(int a, int b, int c, int d, int A, int B, int C, int D):Figure(tetra) {
	std::stringstream message;

    if ((a <= 0) || (b <= 0) || (c <= 0) || (d <= 0))   {
        message.str(std::string());
        message << "Ошибка создания фигуры. Причина: все длины сторон должны быть положительным числом\n";
        throw ValExcept(message.str());
    }
    else if (360 != (A + B + C + D))    {
        message.str(std::string());
        message << "Ошибка создания фигуры. Причина: сумма углов четырехугольника не равна 360\n";
        throw ValExcept(message.str());
    }



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