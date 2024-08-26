#include <iostream>
#include "countr.h"

Counter::Counter() {
    setVal(1);
}
Counter::Counter(int _num) {
    setVal(_num);
}

int Counter::getVal() {
    return this->Value;
}
int Counter::incVal() {
    return (++Value);
}
int Counter::decVal() {
    return (--Value);
}

void Counter::setVal(int _num) {
    this->Value = _num;
}

void cntCalc(Counter& _cntObj) {
    bool a = true;
    do {
        char inpt;
        std::cout << "Введите команду ('+', '-', '=' или 'x'): ";
        std::cin >> inpt;
        switch (inpt) {
        case('+'):
            _cntObj.incVal();
            break;
        case ('-'):
            _cntObj.decVal();
            break;
        case('='):
            std::cout << _cntObj.getVal() << std::endl;
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
};