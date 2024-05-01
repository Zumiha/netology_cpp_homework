#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <algorithm>

template <class T>
void print_container(T stl_c) {
    for_each(stl_c.cbegin(), stl_c.cend(), [](const auto& var) {std::cout << var << " "; });
    std::cout << std::endl;
}

int main (){

    std::set<std::string> test_set = { "one", "two", "three", "four" };
    std::list<std::string> test_list = { "one", "two", "three", "four" };
    std::vector<std::string> test_vector = { "one", "two", "three", "four" };


    print_container(test_set);
    print_container(test_list);
    print_container(test_vector);

    return 0;
}