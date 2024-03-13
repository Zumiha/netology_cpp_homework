#include <iostream>

class Counter
{
public:
    Counter() {
        setVal(1);
    }

    Counter(int num) {
        setVal(num);
    }

    int getVal() {
        return this->Value;
    }

    int incVal() {
        return (++Value);
    }

    int decVal() {
        return (--Value);
    }

private:
    int Value;

    void setVal(int num) {
        this->Value = num;
    }
};

void cntCalc(Counter& count) {
    bool a = true;
    do {
        char inpt;
        std::cout << "Введите команду ('+', '-', '=' или 'x'): ";
        std::cin >> inpt;
        switch (inpt) {
        case('+'):
            count.incVal();
            break;
        case ('-'):
            count.decVal();
            break;
        case('='):
            std::cout << count.getVal() << std::endl;
            break;
        case('x'):
            std::cout << "До свидания! \n";
            a = false;
            break;
        default:
            std::cout << "Не верная команда!\n";
            break;
        }
    } while (a == true);
}

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

    int val;

    if (yesno == "y") {
        std::cout << "Введите начальное значение счётчика: ";
        std::cin >> val;
        Counter count(val);
        cntCalc(count);
    }
    else {
        std::cout << "Начальное значение счётчика: ";
        Counter count;
        std::cout << count.getVal() << std::endl;
        cntCalc(count);
    }

    return 0;
}