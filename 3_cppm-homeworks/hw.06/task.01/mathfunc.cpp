#include <iostream>
#include "mathfunc.h"

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return  a - b;
}

int mult(int a, int b)
{
	return a * b;
}

double divsn(int a, int b)
{
	return static_cast<double>(a) / b;
}

int exp(int a, int b)
{
	int result = a;
	for (int i = 1; i < b; ++i)
		result *= a;
	return result;
}