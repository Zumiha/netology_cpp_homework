#include <iostream>
#include <vector>
#include <algorithm>
#include <future>
#include <random>


std::vector<int> createVector(int size, int _min, int _max) {
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::vector<int> v(size);
    std::uniform_int_distribution<> dis(_min, _max);
    std::generate(v.begin(), v.end(), [&](){return dis(gen);});
    return v;
}

void searchMin(std::vector<int>& _vect, const int& _i, std::vector<int>::iterator& _min_it, std::promise<int> promise) {
    for (std::vector<int>::iterator it = _vect.begin() + _i; it != _vect.end(); it++) {
        if (*it < *_min_it) {_min_it = it;}
    }
    promise.set_value(distance(_vect.begin(), _min_it));
}

void selectSort(std::vector<int>& _vect) {
    std::vector<int>::iterator iter;

    for (auto i = 0; i < _vect.size(); i++) {
        iter  = _vect.begin() + i;
        std::promise<int> min_el_commit;
        std::future<int> min_el_future = min_el_commit.get_future();
        auto ftrs = std::async(searchMin, std::ref(_vect), std::ref(i), std::ref(iter), std::move(min_el_commit));
        ftrs.wait();  

        auto j = min_el_future.get();
        if (_vect[i] != _vect[j]) std::swap(_vect[i],_vect[j]);
    }
    
}


int main() {
    int v_size = 10;
    int min = 1;
    int max = 20;

    auto test_v = createVector(v_size, min, max);

    for (auto& i:test_v) {std::cout << i << " ";} std::cout << std::endl;
	selectSort(test_v);
    for (auto& i:test_v) {std::cout << i << " ";} 
    
    return 0;
}