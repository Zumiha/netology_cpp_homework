#pragma once
#include "SafeQueue.h"
#include <thread>
#include <functional>
#include <future>

class ThreadPool {
public:
	ThreadPool();
	~ThreadPool();

	void work();

	template<typename F>
    void submit(F&& func) {
        auto task = std::make_shared<std::packaged_task<void()>>(std::forward<F>(func));
        work_queue.push([task]() { (*task)(); });
    }

	int getCPUcount() {return cpu_count;}
	int getQueueSize() {return work_queue.size();}
private:
	std::atomic<bool> is_complete{ false };
	const int cpu_count = std::thread::hardware_concurrency();
	std::vector<std::thread> thr_pool;
	SafeQueue<std::function<void()>> work_queue; 
};
