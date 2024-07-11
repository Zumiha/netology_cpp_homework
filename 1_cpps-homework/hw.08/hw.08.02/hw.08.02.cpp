#include <iostream>

namespace sum {
    int calc(int x, int y) {
    return x + y;
    }
}

namespace sub {
    int calc(int x, int y) {
    return x - y;
    }
}

namespace mult {
    int calc(int x, int y) {
    return x * y;
    }
}

namespace divs {
    int calc(int x, int y) {
    return x / y;
    }
}

int main() {
    int x = 6, y = 9;
    std::cout << "x = " << x << ", y = " << y <<std::endl;
    std::cout << "Сложение: " << sum::calc (x, y) << "\n";
    std::cout << "Вычитание: " << sub::calc (x, y) << "\n";
    std::cout << "Умножение: " << mult::calc (x, y) << "\n";
    std::cout << "Деление: " << divs::calc (x, y) << std::endl;
}   