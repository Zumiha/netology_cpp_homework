#include <iostream>
#include "mathfunc.h"

int main()  {
    setlocale(LC_ALL, "Russian");

	int val1 = 0;
	std::cout << "Введите первое число: ";
	std::cin >> val1;

	int val2 = 0;
	std::cout << "Введите второе число: ";
	std::cin >> val2;	

	std::cout << "Выберите операцию (1 - сложение, 2 вычитание, 3 - умножение, 4 - деление, 5 - возведение в степень): ";
	int result;
	std::cin >> result;
	switch (result)
	{
	case 1: std::cout << val1 << " + " << val2 << " = " << add(val1, val2) << std::endl;
		break;
	case 2: std::cout << val1 << " - " << val2 << " = " << sub(val1, val2) << std::endl;
		break;
	case 3: std::cout << val1 << " * " << val2 << " = " << mult(val1, val2) << std::endl;
		break;
	case 4: std::cout << val1 << " / " << val2 << " = " << divsn(val1, val2) << std::endl;
		break;
	case 5: std::cout << val1 << " в степени " << val2 << " = " << exp(val1, val2) << std::endl;
		break;
	default:
		std::cout << "Неправильная операция" << std::endl;
		break;
	}

	return 0;
}
