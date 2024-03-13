#include <iostream>
#include <sstream>
#include <Windows.h>

int main() {
    //setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Введите имя: ";
    std::string usr_in;
    std::cin >> usr_in;
    std::cout << "Здравствуйте, " << usr_in << "!" << std::endl;
    system("pause");

    return 0;
}