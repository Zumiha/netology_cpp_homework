#include <iostream>
#include <sstream>
#include <Windows.h>

int main() {
    //setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "������� ���: ";
    std::string usr_in;
    std::cin >> usr_in;
    std::cout << "������������, " << usr_in << "!" << std::endl;
    system("pause");

    return 0;
}