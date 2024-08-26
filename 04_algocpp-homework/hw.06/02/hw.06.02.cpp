#include <iostream>
#include <string>
#include <cmath>

unsigned long simple_string_hash(std::string str, int p, int n) {
    unsigned long hash_reuslt = 0;
    for (int i = 0; i < str.length(); i++) {
        hash_reuslt += static_cast<int>(str[i])*pow(p,i);
    }
    return hash_reuslt%n;
}   

int main() {

    std::string str;
    unsigned long hash = 0;
    int p, n;

    std::cout << "Введите p: ";
    std::cin >> p;
    std::cout << "Введите n: ";
    std::cin >> n;

    do {
        std::cout << "Введите строку: ";
        std::cin >> str;
        hash = simple_string_hash(str, p, n);
        std::cout << "Хэш строки " << str << " = " << hash << std::endl;
    } while (str != "exit");

    return 0;
}