#include <iostream>
#include <vector>
#include <algorithm>

template <class T>
T powerTwo(T value) {
    return value * value;
}

template <typename T>
std::vector<T> powerTwo(std::vector<T> vec_value) {
    for (auto& i : vec_value)
		i *= i;
    return vec_value;
}

template <class T>
void printVector(T v) {
    for (int i = 0; i < v.size(); i++){
            std::cout << ((i > 0) ? ", " : "") << v[i];
    }
    std::cout << std::endl;
}

int main (){

    int num = 4;
    std::vector<int> num_vec {-1, 4, 8 };

    std::cout << "[IN]: " << num << std::endl;
    std::cout << "[OUT]: " << powerTwo(num) << std::endl;

    std::cout << "[IN]: "; printVector(num_vec);
    std::cout << "[OUT]: "; printVector(powerTwo(num_vec));
    
    return 0;
}   