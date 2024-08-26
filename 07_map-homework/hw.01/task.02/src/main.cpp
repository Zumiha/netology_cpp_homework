// homework_1_2.cpp : MAP-5 Задание 2 «Параллельные вычисления»

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

enum THREAD
{
	THRD_1 = 1,
	THRD_2 = 2,
	THRD_4 = 4,
	THRD_8 = 8,
	THRD_16 = 16
};

enum ELM
{
	EL10_3 = 1000,
	EL10_4 = 10000,
	EL10_5 = 100000,
	EL10_6 = 1000000
};

std::vector<int> createVector(ELM size) {
    srand(time(0));
    std::vector<int> v(size);
    std::generate(v.begin(), v.end(), rand);
    return v;
}

void additionVectors(const std::vector<int>& v1, const std::vector<int>& v2, int beg, int end) {
    int size = v1.size();
	std::vector<int> res (size);
	for (auto i = beg; i < end; ++i) {
		res[i] = v1[i] + v2[i];
	}
}

void vecSum(const THREAD& thread_count, const ELM& vector_size, const std::vector<int>& v1, const std::vector<int>& v2) {
    
    std::vector<std::thread> t0;
    for (int tc = 0; tc < thread_count; tc++) {
        int beg = (vector_size / thread_count) * tc;
        int end = (vector_size / thread_count) * (tc+1) - 1;
        t0.push_back(std::thread(additionVectors, std::ref(v1), std::ref(v2), beg, end));
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (auto& u : t0) u.join();
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration <double> time = end - start;
    std::cout << time.count() << " \t";
}

int main() {

    std::array <THREAD, 5> thr_count{ THRD_1, THRD_2, THRD_4, THRD_8, THRD_16 };
    std::array <ELM, 4> elm_size{ EL10_3, EL10_4, EL10_5, EL10_6};

    std::cout << "Number of concurrent threads supported: ";
    std::cout << std::thread::hardware_concurrency() << std::endl;

    for (auto i : elm_size) std::cout << "\t\t" << i;
    std::cout << std::endl; 

    for (auto threads : thr_count)
	{
		switch (threads)
		{
		case THRD_1:
			std::cout << threads << " thread:\t";
			break;
		case THRD_2:
		case THRD_4:
		case THRD_8:
		case THRD_16:
			std::cout << threads << " threads:\t";
			break;
		}

        for (auto elemnts : elm_size) {
            std::vector<int> v1 = createVector(elemnts);
            std::vector<int> v2 = createVector(elemnts);
            vecSum(threads, elemnts, v1, v2);
        }

        std::cout << std::endl;
	}


        
    return 0;
}

