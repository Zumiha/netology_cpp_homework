#include "ThreadPool.h"

ThreadPool::ThreadPool() {
	for (int i = 0; i < cpu_count; ++i) {
		thr_pool.push_back(std::thread(&ThreadPool::work, this));
	}
}
ThreadPool::~ThreadPool() {
	is_complete = true;
	for (auto& el : thr_pool) {el.join();}
}

void ThreadPool::work() {
	while (!is_complete) {
		std::function<void()> f{};
		if (work_queue.pop(f)) {f();} 
		else {std::this_thread::yield();}
	}
}