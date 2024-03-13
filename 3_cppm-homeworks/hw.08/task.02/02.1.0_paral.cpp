#include "02.1.0_paral.h"
#include "ValError.h"
#include <iostream>
#include <sstream>

Parallelogram::Parallelogram(int a, int b, int c, int d, int A, int B, int C, int D) : Quadrilateral(a, b, c, d, A, B, C, D) {
	std::stringstream message;

    if ((a != c) && (b != d))   {
        message.str(std::string());
        message << "Ошибка создания фигуры. Причина: стороны a,c и b,d должны быть попарно равны\n";
        throw ValExcept(message.str());
    } else if ((A != C) && (B != D))    {
        message.str(std::string());
        message << "Ошибка создания фигуры. Причина: углы A,C и B,D должны быть попарно равны\n";
        throw ValExcept(message.str());        
    }

    setName("Параллелограм");
}