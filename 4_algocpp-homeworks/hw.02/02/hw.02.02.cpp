#include <iostream>

int Fibonacci(int fibArr[], const int size) {
    fibArr[0] = 0;
    fibArr[1] = 1;

    for (long long i = 2; i <= size; i++)   {
        fibArr[i] = fibArr[i - 1] + fibArr[i - 2];
    }
    return fibArr[size];
}

int main() {

    int size = 0;
    std::cout << "Введите индекс числа Фибоначчи: ";
    std::cin >> size;

    int* fibArr = new int[size + 1] {};

    std::cout << "Число Фибоначчи: " << Fibonacci(fibArr, size) << std::endl;

    delete[] fibArr;

    return 0;
}