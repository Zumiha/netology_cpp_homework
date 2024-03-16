#include "01.0_triangle.h"
#include "ValError.h"
#include <iostream>
#include <sstream>

Triangle::Triangle(int a, int b, int c, int A, int B, int C):Figure(tri) {
    
    std::stringstream message;

    if ((a <= 0) || (b <= 0) || (c <= 0))   {
        message.str(std::string());
        message << "Ошибка создания фигуры. Причина: все длины сторон должны быть положительным числом\n";
        throw ValExcept(message.str());
    }
    else if (((a + b) <= c) || ((b + c) <= a) || ((a + c) <= b))    {
        message.str(std::string());
        message << "Ошибка создания фигуры. Причина: сумма длин любых двух сторон треугольника должна быть строго больше длинны третьей стороны\n";
        throw ValExcept(message.str());
    }
    else if (180 != (A + B + C))    {
        message.str(std::string());
        message << "Ошибка создания фигуры. Причина: сумма углов треугольника не равна 180\n";
        throw ValExcept(message.str());
    }
     
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
