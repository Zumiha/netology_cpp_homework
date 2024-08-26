#pragma once
#include "SafeQueue.h"
#include <thread>
#include <functional>

class ThreadPool {
public:
	ThreadPool();
	~ThreadPool();

	void work();
	void submit(std::function<void()>&& func);
private:
	std::atomic<bool> is_complete{ false };
	const int cpu_count = std::thread::hardware_concurrency();
	std::vector<std::thread> thr_pool;
	SafeQueue<std::function<void()>> work_queue; 
};
