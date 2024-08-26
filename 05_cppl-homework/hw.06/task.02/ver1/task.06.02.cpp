#include <iostream>
#include <set>

int main() {

    std::cout << "[IN]: " << std::endl;
    int amount = 0; 
    std::cin >> amount;
    
    std::set<int, std::greater<>> mm;
    int number;
    int count = 0;
    while (count < amount) {
        std::cin >> number;
        mm.insert(number);
        count++;
    }
    std::cout << "[OUT]: " << std::endl;
    for (const auto& var : mm) {
        std::cout << var << std::endl;
    }
    return 0;
}

