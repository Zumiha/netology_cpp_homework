#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>


template <class T>
class SafeQueue {
public:
	SafeQueue () {}
	~SafeQueue () {}

	void push(T ext_push_val) {
		std::unique_lock<std::mutex> mtx_lock(mtx);
		queue.push(std::move(ext_push_val));
		queue_is_empty = false;
		condt_var.notify_one();
	};

	bool pop(T& pop_val) {
		std::unique_lock<std::mutex> mtx_lock(mtx);
		while(queue_is_empty) {
			condt_var.wait(mtx_lock);
		}
		if (queue.empty()) { 
			return false;
		} else {
			pop_val = std::move(queue.front());
			queue.pop();
			return true;
		}
	}

private:
	mutable std::mutex mtx;
	std::atomic<bool> queue_is_empty{true};
	std::condition_variable condt_var;
	std::queue<T> queue;
};