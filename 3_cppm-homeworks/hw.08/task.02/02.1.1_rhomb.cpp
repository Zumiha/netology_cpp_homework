#include "02.1.1_rhomb.h"
#include "ValError.h"
#include <iostream>
#include <sstream>

Rhombus::Rhombus(int a, int b, int c, int d, int A, int B, int C, int D) : Parallelogram(a, b, c, d, A, B, C, D) {
	std::stringstream message;

    if (a != b)   {
        message.str(std::string());
        message << "Ошибка создания фигуры. Причина: все стороны должны равны\n";
        throw ValExcept(message.str());
    }

    setName("Ромб");
}