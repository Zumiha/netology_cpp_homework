#include <iostream>
#include <vector>
#include <algorithm>

template <class T>void moveVectors(std::vector<T>& _src, std::vector<T>& _dest){
    std::vector<T> tmp = std::move(_dest);
    _dest = std::move(_src);
    _src = std::move(tmp);
}

void printVector(std::vector<std::string>& _vec) {
    for (const std::string& st : _vec) {
        std::cout << st << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::vector <std::string> one = { "test_string1", "test_string2" };
    std::vector <std::string> two;
    std::cout << "one: "; printVector(one);
    std::cout << "two: "; printVector(two);

    std::cout << std::endl;
    moveVectors(two, one);
    
    std::cout << "one: "; printVector(one);
    std::cout << "two: "; printVector(two);
}