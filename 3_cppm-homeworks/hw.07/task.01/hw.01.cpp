#include <iostream>
#define MODE 1

#ifndef MODE
#error Сonstant is not defined
#endif

#if MODE == 1
int add(int _a, int _b) {
    return (_a + _b);
}
#endif


int main() {

    setlocale(LC_ALL, "Russian");

#if MODE == 0 
    std::cout << "Работаю в режиме тренировки" << std::endl;
#elif MODE == 1
    int a, b;
    std::cout << "Работаю в боевом режиме" << std::endl;
    std::cout << "Введите число 1: ";
    std::cin >> a;
    std::cout << "Введите число 2: ";
    std::cin >> b;
    std::cout << "Результат сложения: " << add(a, b) << std::endl;
#else
    std::cout << "Неизвестный режим.Завершение работы" << std::endl;
#endif
    return 0;
}