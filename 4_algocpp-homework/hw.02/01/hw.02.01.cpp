#include <iostream>

int fibCount(int n)
{
    return n < 2 ? n : fibCount(n - 2) + fibCount(n - 1);
}

int main () {
    int num = 0;
    std::cout << "Введите индекс числа: ";
    std::cin >> num;
    std::cout << "Число Фибоначчи: " << fibCount(num);
    return 0;
}