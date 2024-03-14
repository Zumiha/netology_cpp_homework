#include <iostream>

class Calculator {

private:
    double num1;
    double num2;

public:
    bool set_num1(double num1) {
        if (num1 != 0) {
            this->num1 = num1;
            return true;
        }
        else {
            return false;
        }
    }
    bool set_num2(double num2) {
        if (num2 != 0) {
            this->num2 = num2;
            return true;
        }
        else {
            return false;
        }
    }
    double add() {
        return (num1 + num2);
    }
    double multiply() {
        return (num1 * num2);
    }
    double subtract_1_2() {
        return (num1 - num2);
    }
    double subtract_2_1() {
        return (num2 - num1);
    }
    double divide_1_2() {
        return (num1 / num2);
    }
    double divide_2_1() {
        return(num2 / num1);
    }

    void input_num1() {
        double num_v = 0;
        do {
            std::cout << "Введите num1: ";
            std::cin >> num_v;

            if (set_num1(num_v) == false) {
                std::cout << "Неверный ввод!" << std::endl;
                continue;
            }
            else { break; }
        } while (true);
    }

    void input_num2() {
        double num_v = 0;
        do {
            std::cout << "Введите num2: ";
            std::cin >> num_v;

            if (set_num2(num_v) == false) {
                std::cout << "Неверный ввод!" << std::endl;
                continue;
            }
            else { break; }
        } while (true);
    }

    void perfOper() {

        std::cout << "num1 + num2 = " << add() << std::endl;
        std::cout << "num1 - num2 = " << subtract_1_2() << std::endl;
        std::cout << "num2 - num1 = " << subtract_2_1() << std::endl;
        std::cout << "num1 * num2 = " << multiply() << std::endl;
        std::cout << "num1 / num2 = " << divide_1_2() << std::endl;
        std::cout << "num2 / num1 = " << divide_2_1() << std::endl;

    }

};

int main()
{
    setlocale(LC_ALL, "Russian");
    Calculator calc;

    do {
        calc.input_num1();
        calc.input_num2();
        calc.perfOper();
    } while (true);

    return 0;
}
