#include <iostream>

void counting_function () {
    static int count = 0;
    count ++;    
    std::cout << "Количество вызовов функции counting_function(): " << count << std::endl;
}

int main() {
    for (int i = 0; i < 15; i++) {
        counting_function();
    }
}