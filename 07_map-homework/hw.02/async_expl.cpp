#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <mutex>
#include <atomic>
#include <Windows.h>

enum THREAD {THRD_1 = 1,THRD_2 = 2,THRD_4 = 4,THRD_8 = 8};
enum ELM {EL10_3 = 1000,EL10_4 = 10000,EL10_5 = 100000,EL10_6 = 1000000};

class Chronos {
private:
	std::chrono::system_clock::time_point born;
	std::chrono::system_clock::time_point dead;

	bool chronos_alive = false;

public:

	Chronos(): born(std::chrono::system_clock::now()), chronos_alive(true) {}

	void collapse() {
		this->dead = std::chrono::system_clock::now();this->chronos_alive = false;
	}

	double time_elapsed () {
		return std::chrono::duration_cast<std::chrono::milliseconds>(this->dead - this->born).count();
	}
};

class BarProcess {
private:
	std::atomic<int> prog_pos;
	std::vector<int> vectorExample;
	ELM size;
	THREAD thread_count;
	double time_spent;
	std::mutex mtx;

	std::vector<int> createVector(ELM size) {
		srand(time(0));
		std::vector<int> v(size);
		std::generate(v.begin(), v.end(), rand);
		return v;
	}

	
	void vecSum(int beg, int end) {
		std::vector<int> v1 = createVector(this->size);
		std::vector<int> v2 = createVector(this->size);
		for (auto i = beg; i < end; ++i) {
			this->vectorExample[i] = v1[i] + v2[i];
		}
	}

	void progCalculs() {		
		std::vector<std::thread> t0;
		for (int tc = 0; tc < this->thread_count; tc++) {
			int beg = (this->size / this->thread_count) * tc;
			int end = (this->size / this->thread_count) * (tc+1) - 1;
			t0.push_back(std::thread(vecSum, this, beg, end));
		}

		auto start = std::chrono::high_resolution_clock::now();
		for (auto& u : t0) u.join();
		auto end = std::chrono::high_resolution_clock::now();
		
		std::chrono::duration <double> time = end - start;
		std::cout << time.count() << " \t";
	}

public:
	BarProcess() : thread_count(THRD_1), size(EL10_3), vectorExample(createVector(size)) {}
	BarProcess(THREAD t_c, ELM v_c) : thread_count(t_c), size(v_c), vectorExample(createVector(size)) {}
	~BarProcess(){}

	void objWork() {
		Chronos clock;
		progCalculs();
		clock.collapse();
		this->time_spent = clock.time_elapsed();
	}

	int checkProgress() {
		return prog_pos;
	}

};

// void VerySlowSort_in_parallel(int num) {
// 	Chronos bb;
// 	char Loaded = 219;

// 	int load = 0;

// 	std::call_once(flag, []() {
// 		std::cout << "# id\t   bar\t\t time";
// 		});

// 	{
// 		std::lock_guard<std::mutex> lckmtx(mtx);
// 		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
// 			{
// 				static_cast<SHORT>(0), static_cast<SHORT>(num + 1)
// 			});
// 		std::cout << num << " " << std::this_thread::get_id();
// 	}

// 	for (int i = 0; i < 10; i++) {
// 		std::this_thread::sleep_for(std::chrono::milliseconds(100 * (num + 1))); {
// 			std::lock_guard<std::mutex> lckmtx(mtx);
// 			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {static_cast<SHORT>(i + 10), static_cast<SHORT>(num + 1)});

// 			std::cout << Loaded;
// 			load++;
// 		}
// 	}
// 	{
// 		std::lock_guard<std::mutex> lckmtx(mtx);
// 		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
// 			{
// 				static_cast<SHORT>(25), static_cast<SHORT>(num + 1)
// 			});
// 		bb.collapse();
// 	}
// }
std::mutex mtxx;

void threadTask(BarProcess& _obj) {
	std::cout << "object this\n" << std::endl;
}

int main() {

    std::vector<std::thread> threads;
	BarProcess o_a;
	BarProcess o_b(THRD_2, EL10_4);
	BarProcess o_c(THRD_1, EL10_4);
	BarProcess o_d(THRD_4, EL10_6);
	BarProcess o_e(THRD_8, EL10_6);
	BarProcess o_f(THRD_4, EL10_5);

	threads.push_back(std::thread(threadTask, std::ref(o_a)));
	threads.push_back(std::thread(threadTask, std::ref(o_b)));
	threads.push_back(std::thread(threadTask, std::ref(o_c)));
	threads.push_back(std::thread(threadTask, std::ref(o_d)));
	threads.push_back(std::thread(threadTask, std::ref(o_e)));
	threads.push_back(std::thread(threadTask, std::ref(o_f)));
    
    for (std::thread& t : threads) {
        t.join();
    }
    return 0;
}