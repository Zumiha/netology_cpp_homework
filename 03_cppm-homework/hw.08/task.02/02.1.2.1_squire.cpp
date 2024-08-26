#include "02.1.2.1_squire.h"
#include "ValError.h"
#include <iostream>
#include <sstream>

Square::Square(int a, int b, int c, int d, int A, int B, int C, int D) : Rectangle(a, b, c, d, A, B, C, D) {
	std::stringstream message;

    if ((a != b) || (a != c) || (a != d))   {
        message.str(std::string());
        message << "Ошибка создания фигуры. Причина: все стороны должены быть равны\n";
        throw ValExcept(message.str());
    }
    setName("Квадрат");
}