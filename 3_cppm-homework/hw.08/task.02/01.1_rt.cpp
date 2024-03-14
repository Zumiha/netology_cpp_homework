#include "01.1_rt.h"
#include "ValError.h"
#include <iostream>
#include <sstream>

RightTriangle::RightTriangle(int a, int b, int c, int A, int B, int C) : Triangle(a, b, c, A, B, C) {
	
	std::stringstream message;

    if ((C != 90))   {
        message.str(std::string());
        message << "Ошибка создания фигуры. Причина: угол C должен быть равен 90°\n";
        throw ValExcept(message.str());
    }
	
	setName("Прямоугольный треугольник");
}

