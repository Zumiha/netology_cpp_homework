#include "ThreadPool.h"
#include <iostream>
#include <chrono>


using namespace std::chrono_literals;

void fucntionOne() {
    std::this_thread::sleep_for(800ms);
    std::cout << "function 1 working...\n";
}

int fucntionTwo() {
    std::this_thread::sleep_for(2000ms);
    std::cout << "function 2 working...\n";
	return 8;
}

int main() {
    ThreadPool pool_obj;
	for (int i = 0; i < 10; ++i) {
        pool_obj.submit(fucntionOne);
        pool_obj.submit(fucntionTwo);
        std::this_thread::sleep_for(500ms);
    }
}
