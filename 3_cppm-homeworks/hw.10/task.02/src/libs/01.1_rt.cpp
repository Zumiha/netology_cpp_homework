#include "01.1_rt.h"

RightTriangle::RightTriangle(int a, int b, int c, int A, int B) : Triangle(a, b, c, A, B, 90) {
	setName("Прямоугольный треугольник");
}

