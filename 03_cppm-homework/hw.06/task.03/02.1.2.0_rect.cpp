#include "02.1.2.0_rect.h"

Rectangle::Rectangle(int a, int b) : Parallelogram(a, b, 90, 90) {
	setName("Прямоугольник");
}