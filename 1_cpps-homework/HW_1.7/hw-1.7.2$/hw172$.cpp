#include <iostream>

void swap (int& a, int& b) {
    a = a + b;
    b = a - b;
    a = a - b;
}

int main(int argc, char** argv)
{
	int a = 0, b = 1;

	std::cout << "a = " << a << ", b = " << b << std::endl;

	swap(a, b);

	std::cout << "a = " << a << ", b = " << b << std::endl;

	return 0;
}