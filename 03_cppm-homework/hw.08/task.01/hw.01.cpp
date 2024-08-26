#include <iostream>
#include <sstream>
#include <Windows.h>

int function(std::string str, int forbidden_length) {
    if ((str.length()) == forbidden_length) throw "Вы ввели слово запретной длинны! До свидания";
    return (str.length());
}


int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);

    std::cout << "Введите запретную длину: ";
    int f_word_len = 0;
    std::cin >> f_word_len;
    std::string f_word;

    do {
        std::cout << "Введите слово: ";
        std::cin >> f_word;
        try {
            std::cout << "Длина слова \"" << f_word << "\" равна " << function(f_word, f_word_len) << std::endl;
        }
        catch (const char* f_len) {
            std::cout << f_len << std::endl;
            break;
        }
    } while (true);    

    return 0;
}
