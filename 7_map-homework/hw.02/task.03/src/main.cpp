#include <iostream>
#include <mutex>

#include <vector>
#include <thread>

#include <chrono>

class Data {
private:
    int value;
public:
    Data (int input_val) : value(input_val) {}
    ~Data () {}
    int getVal() {return this->value;}
    void setVal(int _a) {this->value = _a;}
    std::mutex mutex;
};

void swapLock(Data& _a, Data& _b) {
    std::lock (_a.mutex, _b.mutex);
    int temp = _a.getVal();
    _a.setVal(_b.getVal());
    _b.setVal(temp);
    _a.mutex.unlock(); _b.mutex.unlock();
}

void sawpScopedLock (Data& _a, Data& _b) {
    std::scoped_lock scope_lock (_a.mutex, _b.mutex);
    int temp = _a.getVal();
    _a.setVal(_b.getVal());
    _b.setVal(temp);
}

void sawpUniqueLock (Data& _a, Data& _b) {
    std::unique_lock unq_lock1 (_a.mutex);
    std::unique_lock unq_lock2 (_b.mutex);
    int temp = _a.getVal();
    _a.setVal(_b.getVal());
    _b.setVal(temp);    
}

enum TYPE {SL,SSL,SUL};
void swapper (Data& _a, Data& _b, TYPE code, int timer);

int main() {
    Data a_data(13), b_data(37);

    std::cout << "Before swapLock: a_data = " << a_data.getVal() << ", b_data = " << b_data.getVal() << std::endl;
    swapLock(a_data, b_data);
    std::cout << "After swapLock: a_data = " << a_data.getVal() << ", b_data = " << b_data.getVal() << std::endl;
    std::cout << std::endl;

    a_data.setVal(31), b_data.setVal(49);
    std::cout << "Before sawpScopedLock: a_data = " << a_data.getVal() << ", b_data = " << b_data.getVal() << std::endl;
    sawpScopedLock(a_data, b_data);
    std::cout << "After sawpScopedLock: a_data = " << a_data.getVal() << ", b_data = " << b_data.getVal() << std::endl;
    std::cout << std::endl;

    a_data.setVal(73), b_data.setVal(97);
    std::cout << "Before sawpUniqueLock: a_data = " << a_data.getVal() << ", b_data = " << b_data.getVal() << std::endl;
    sawpUniqueLock(a_data, b_data);
    std::cout << "After sawpUniqueLock: a_data = " << a_data.getVal() << ", b_data = " << b_data.getVal() << std::endl;
    std::cout << std::endl;



    // a_data.setVal(37), b_data.setVal(73);
    
    // std::cout << "Before swapping: a_data = " << a_data.getVal() << ", b_data = " << b_data.getVal() << std::endl;
    // std::cout << std::endl;
    // std::vector<std::thread> thrd_v;
    // thrd_v.push_back(std::thread(swapper, std::ref(a_data), std::ref(b_data), SL, 300));
    // std::cout << "After thread1: a_data = " << a_data.getVal() << ", b_data = " << b_data.getVal() << std::endl;
    // thrd_v.push_back(std::thread(swapper, std::ref(a_data), std::ref(b_data), SSL, 200));
    // std::cout << "After thread2: a_data = " << a_data.getVal() << ", b_data = " << b_data.getVal() << std::endl;
    // thrd_v.push_back(std::thread(swapper, std::ref(a_data), std::ref(b_data), SUL, 100));
    // std::cout << "After thread3: a_data = " << a_data.getVal() << ", b_data = " << b_data.getVal() << std::endl;
    // std::cout << std::endl;
    // for (auto& i : thrd_v) {i.join();}
    // std::cout << "After swapping: a_data = " << a_data.getVal() << ", b_data = " << b_data.getVal() << "\n" << std::endl;

    return 0;
}

void swapper (Data& _a, Data& _b, TYPE code, int timer) {
    switch (code) {
    case SL:
        std::this_thread::sleep_for(std::chrono::milliseconds(timer));
        swapLock(_a, _b);
        break;

    case SSL:
        std::this_thread::sleep_for(std::chrono::milliseconds(timer));
        sawpScopedLock(_a, _b);
        break;

    case SUL:
        std::this_thread::sleep_for(std::chrono::milliseconds(timer));
        sawpUniqueLock(_a, _b);
        break;
    
    default:
        break;
    }
}