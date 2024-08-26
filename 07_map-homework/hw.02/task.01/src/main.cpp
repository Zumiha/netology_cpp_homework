#include <iostream>
#include <thread>
#include <atomic>

void clientQueue(std::atomic<int>& current, int _max_queue) {
	do
	{   
        std::cout << "\nclients - " << current << " query size. New request registration";
		// std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "\nclients - line size: " << ++current;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	} while (current != _max_queue);
}

void operatorConvey(std::atomic<int>& current) {
	int total_request_done = 0;
    do
	{
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        std::cout << "\noperator - requests left: " << current;
		// std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		std::cout << "\noperator processed query"; --current; ++total_request_done;
	} while (0 < current);
    std::cout << "\n\noperator processed " << total_request_done << " requests total." <<std::endl;
}

int main()
{
	int max_queue = 4;
    std::atomic<int> queue = 0;

	std::thread client_thread(clientQueue, std::ref(queue), max_queue);    
	std::thread operator_thread(operatorConvey, std::ref(queue));	
    client_thread.join();
	operator_thread.join();

	return 0;
}