#include <iostream>
#include <string>

int simple_string_hash(std::string str) {
    int hash_reuslt = 0;
    for (int i = 0; i < str.length(); i++) {
        hash_reuslt += static_cast<int>(str[i]);
    }
    return hash_reuslt;
}   

int main() {

    std::string str;
    int hash = 0;

    do {
        std::cout << "Введите строку: ";
        std::cin >> str;
        hash = simple_string_hash(str);
        std::cout << "Наивный хэш строки " << str << " = " << hash << std::endl;
    } while (str != "exit");

    return 0;
}