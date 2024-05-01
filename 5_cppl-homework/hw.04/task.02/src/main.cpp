#include <iostream>
#include "LinkedList.h"

int main(){
    std::cout << "Hello List!" << std::endl;
    List test_list;
    test_list.PushFront(1);
    test_list.PushFront(0);
	test_list.PushBack(2);
    std::cout << test_list.PopBack() << std::endl;
    return 0;
}