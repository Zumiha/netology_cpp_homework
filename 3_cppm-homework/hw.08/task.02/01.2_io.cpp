#include "01.2_io.h"
#include "ValError.h"
#include <iostream>
#include <sstream>

IsoTriangle::IsoTriangle(int a, int b, int c, int A, int B, int C) : Triangle(a, b, c, A, B, C) {
	std::stringstream message;

    if (a != c)   {
        message.str(std::string());
        message << "Ошибка создания фигуры. Причина: стороны a и c должны быть равны\n";
        throw ValExcept(message.str());
    } else if (A != C)   {
        message.str(std::string());
        message << "Ошибка создания фигуры. Причина: углы A и C должны быть равны\n";
        throw ValExcept(message.str());
    }
	
	setName("Равнобедренный треугольник");
}
