#include <iostream>
#include <string>
#include <cmath>

int StrHash(std::string str, int len, int prime) {
    int hash_reuslt = 0;
    for (int i = 0; i < len; i++) {
        hash_reuslt += static_cast<int>(str[i])*pow(prime,i);
    }
    return hash_reuslt;
}   

int find_substring_light_rabin_karp(std::string source, std::string substring)  {
    const int pn = 1861;
    int s_len = source.length();
    int p_len = substring.length();
    int i, j, s_hash; 
    int p_hash = StrHash(substring, p_len, pn); 


    for (i = 0; i <= s_len - p_len; i++) {
        if (i == 0) {
            s_hash = StrHash(source, p_len, pn);
        }
        else {
            s_hash -= source[i - 1];
            s_hash /= pn;
            s_hash += source[i + p_len - 1] * pow(pn, p_len - 1);
        }
        if (s_hash != p_hash) {
            continue;
        }
        for (j = 0; j < p_len; j++) {
            if (source[i + j] != substring[j]) {
                break;
            }
        }
        if (j == p_len) {
            return i;
        }
    }

    return -1;
}
    

int main() {

    std::string str;
    std::string substr;
    int index = 0;
    
    std::cout << "Введите строку, в которой будет осуществляться поиск: ";
    std::cin >> str;

    do {
        std::cout << "Введите подстроку, которую нужно найти: ";
        std::cin >> substr;
        index = find_substring_light_rabin_karp(str, substr);
        if (index != -1) {
            std::cout << "Подстрока  " << substr << " найдена по индексу " << index << std::endl;
        }
        else {
            std::cout << "Подстрока  " << substr << " не найдена " << std::endl;
        }
    } while (substr != "exit");

    return 0;
}