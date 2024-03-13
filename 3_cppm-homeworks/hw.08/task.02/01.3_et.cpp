#include "01.3_et.h"
#include "ValError.h"
#include <iostream>
#include <sstream>

EquiTriangle::EquiTriangle(int a, int b, int c, int A, int B, int C) : Triangle(a, b, c, A, B, C) {
    std::stringstream message;

    if ((a != b) && (b != c) && (a != c))   {
        message.str(std::string());
        message << "Ошибка создания фигуры. Причина: все стороны должны быть равны\n";
        throw ValExcept(message.str());
    }

    if ((A != B) && (B != C) && (A != C))   {
        message.str(std::string());
        message << "Ошибка создания фигуры. Причина: все углы должны быть равны 60°\n";
        throw ValExcept(message.str());
    }
    
    setName("Равносторонний треугольник");
}