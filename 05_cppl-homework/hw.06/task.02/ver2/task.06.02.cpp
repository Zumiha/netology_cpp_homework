#include <iostream>
#include <vector>
#include <algorithm>

int main() {

    std::cout << "[IN]: " << std::endl;
    int amount = 0; 
    std::cin >> amount;
    
    std::vector<int> vctr_set;
    int number;
    int count = 0;
    while (count < amount) {
        std::cin >> number;
        vctr_set.push_back(number);
        count++;
    }
    std::sort(vctr_set.begin(),vctr_set.end(), std::greater<int>());
    auto var = std::unique(vctr_set.begin(), vctr_set.end());
    
    vctr_set.erase(var, vctr_set.end());


    std::cout << "[OUT]: " << std::endl;
    for (const auto& var : vctr_set) {
        std::cout << var << std::endl;
    }
    return 0;
}

