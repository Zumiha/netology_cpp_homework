#include <iostream>
#include "countr.h"

int main() {

    setlocale(LC_ALL, "Russian");

    std::string yesno;

    do
    {
        std::cout << "Вы хотите указать начальное значение счётчика? Введите (y/n): ";
        std::cin >> yesno;
        if (yesno != "y" && yesno != "n")
            std::cout << "Неправильный ввод. Повторите." << std::endl;
    } while (!((yesno == "y") || (yesno == "n")));

    int startval;

    if (yesno == "y") {
        std::cout << "Введите начальное значение счётчика: ";
        std::cin >> startval;
        Counter CntrNew(startval);
        cntCalc(CntrNew);
    }
    else {
        std::cout << "Начальное значение счётчика: ";
        Counter CntrNew;
        std::cout << CntrNew.getVal() << std::endl;
        cntCalc(CntrNew);
    }

    return 0;
}
