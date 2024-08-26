#include <iostream>
#include <vector>
#include <iterator>

#include <math.h>
#include <algorithm>
#include <random>

#include <thread>
#include <atomic>
#include <future>

namespace parallel {
    template <typename Iterator, typename Funct>
    void for_each(Iterator begin, Iterator end, Funct function) {
        unsigned int size = std::distance(begin, end);
        if (size < std::thread::hardware_concurrency())  {std::for_each(begin, end, function);} 
        else {
            Iterator middle = begin;
            std::advance(middle, size / 2);
            std::future<void> first_half_result = std::async(parallel::for_each <Iterator, Funct>, begin, middle, function);
            first_half_result.get();
            // parallel::for_each(middle, end, function);
            std::future<void> secnd_half_result = std::async(parallel::for_each <Iterator, Funct>, middle, end, function);
            secnd_half_result.get();
        }
    }

}

std::vector<int> createVector(int size, int _min, int _max) {
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::vector<int> v(size);
    std::uniform_int_distribution<> dis(_min, _max);
    std::generate(v.begin(), v.end(), [&](){return dis(gen);});
    return v;
}

int main() {
    auto vector_ = createVector(19, 0, 33);
    
    // std::vector<int> vector_ = {0,1,2,3,4,5,6,7,8,9};

    parallel::for_each(vector_.begin(), vector_.end(), [](int i) {std::cout << i << " ";});

    return 0;
}