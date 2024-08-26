#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <iterator>
#include <Windows.h>


template <class T>
void print_container(T stl_c) {
    for (auto item = stl_c.cbegin(); item != stl_c.cend(); std::advance(item, 1)){
        std::cout << *item << ((item != std::prev(stl_c.cend())/*семь бед, один ответ - костыль и велосипед*/) ? ", " : " ");
    }
    std::cout << std::endl;
}

template <>
void print_container(std::set<std::string> stl_c) {
    for (auto item = stl_c.cbegin(); item != stl_c.cend(); std::advance(item, 1)){
        std::cout << *item << ((item != std::prev(stl_c.cend())) ? " " : ". do you remember the reason for this order? :)");
    }
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