#include "02.1.2.0_rect.h"
#include "ValError.h"
#include <iostream>
#include <sstream>

Rectangle::Rectangle(int a, int b, int c, int d, int A, int B, int C, int D) : Parallelogram(a, b, c, d, A, B, C, D) {
	
	std::stringstream message;

    if ((A != 90) || (B != 90)|| (C != 90)|| (D != 90))   {
        message.str(std::string());
        message << "Ошибка создания фигуры. Причина: все углы должены быть равны 90°\n";
        throw ValExcept(message.str());
    }
	setName("Прямоугольник");
}