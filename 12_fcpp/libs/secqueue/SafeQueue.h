#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>


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
        
        // Ждем, чтобы предотвратить блокировку.
        if (condt_var.wait_for(lock, std::chrono::milliseconds(100), [this] { return !queue.empty(); })) {
            pop_val = std::move(queue.front());
            queue.pop();
            return true;
        }
        return false;
	}

	size_t size() const {
        std::lock_guard<std::mutex> mtx_lock(mtx);
        return queue.size();
    }

    bool empty() const {
        std::lock_guard<std::mutex> mtx_lock(mtx);
        return queue.empty();
    }

private:
	mutable std::mutex mtx;
	std::atomic<bool> queue_is_empty{true};
	std::condition_variable condt_var;
	std::queue<T> queue;
};