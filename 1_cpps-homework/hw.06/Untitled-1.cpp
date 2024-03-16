#include <iostream>

void print_fbnci (int);
int fbnci (int);

int main(int argc, char** argv) {
    
    std::cout << "Введите число: ";
    unsigned int val;
    std::cin >> val;

    std::cout << "Числа Фибоначчи: ";
    print_fbnci(val);
    return 0;
}

void print_fbnci (int result) {
    for (int i = 0; i < result; i++) {
        std::cout << fbnci(i) << " ";
  }
}

int fbnci (int n) {
    return (n < 2) ? n : fbnci(n-1)+fbnci(n-2);
}