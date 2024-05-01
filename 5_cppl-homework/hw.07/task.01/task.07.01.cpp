#include <iostream>
#include <vector>
#include <algorithm>

int main() {
        
    std::vector<int> vectorV = {1, 1, 2, 5, 6, 1, 2, 4};

    std::cout << "[IN]: "; for (const auto& var : vectorV) std::cout << var << ' '; std::cout << std::endl;

    std::sort(vectorV.begin(),vectorV.end());
    auto var = std::unique(vectorV.begin(), vectorV.end());
    vectorV.erase(var, vectorV.end());

    std::cout << "[OUT]: "; for (const auto& var : vectorV) std::cout << var << ' '; std::cout << std::endl;

    return 0;
}