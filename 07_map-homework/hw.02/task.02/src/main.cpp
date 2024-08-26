#include <iostream>
#include <atomic>
#include <thread>
#include <windows.h>
#include <vector>
#include <mutex>
#include <chrono>

using namespace std::chrono_literals;

std::mutex mtx;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);


class Chronos {
private:
	std::chrono::system_clock::time_point born;
	std::chrono::system_clock::time_point dead;
	bool chronos_alive = false;
	double lived;
public:
	Chronos(): born(std::chrono::system_clock::now()), chronos_alive(true) {}
	void collapse() {
		this->dead = std::chrono::system_clock::now(); this->chronos_alive = false;
		this->lived = std::chrono::duration_cast<std::chrono::milliseconds>(this->dead - this->born).count()/1000.0;
	}
	double getLived() {
		return this->lived;
	}
};

void moveCursor(short column, short line) {
    COORD coord{column, line};
    SetConsoleCursorPosition(handle, coord);
}

COORD CslCursorPos(HANDLE CslOutput) {
    CONSOLE_SCREEN_BUFFER_INFO abcd;
    if (GetConsoleScreenBufferInfo(CslOutput, &abcd)) {
        return abcd.dwCursorPosition;
    } else {
        return { 0, 0 };
    }
}

class BarProgress {
private:
    int bar_number = 0;
    int prog_counter = 0;
    COORD bar_progres_pos = { 0,0 };
public:
    BarProgress(const int& line_num) : bar_number(line_num) {printProgress();}
    ~BarProgress(){}

    void printProgress() {
        

        std::unique_lock<std::mutex> lk(mtx);
        moveCursor(0, static_cast<short>(bar_number));
        std::cout << bar_number << "\t" << std::this_thread::get_id() << "\t";
        COORD progress_start_pos = CslCursorPos(handle);
        bar_progres_pos = { progress_start_pos.X, static_cast<short>(bar_number)};
        std::cout << "---------- ";
        COORD persent_pos = CslCursorPos(handle);
        std::cout << 0 << "%";

		Chronos clock;

        for (int i = 1; i < 101; ++i) {
            lk.unlock();
            std::this_thread::sleep_for(bar_number * 37ms);
            lk.lock();

            moveCursor(persent_pos.X, persent_pos.Y);
            std::cout << i << '%';

            if (i % 10 == 0) {
                moveCursor(bar_progres_pos.X, bar_progres_pos.Y);
                std::cout << char(219);
                ++bar_progres_pos.X;
            }
            prog_counter = i;
        }
        if (prog_counter == 100) {
			clock.collapse();
			std::cout << "\t  " << clock.getLived() << "s";
        }
    }
};

void taskFunc(const int coeff) {
    BarProgress objt(coeff);
}

int main() {
    int thrd_cnt = 3;
    std::vector<std::thread> thrds_v;

    system("cls");
    std::cout << "#\tID\tProgress Bar\t  Time" << std::endl;

    for (int i = 1; i < thrd_cnt + 1; ++i) {
        thrds_v.push_back(std::thread(taskFunc, i));
    }
	for (auto &i : thrds_v) {i.join();}
}
