#include <iostream>
#include <algorithm>


class CountFunctor {
private:
    int sum_three_divisions;
    int counts_three_divisions;
public:
    CountFunctor() : sum_three_divisions(0), counts_three_divisions(0) {}
    
    void operator()(int i) {
        if (i % 3 == 0) {
            counts_three_divisions++;
            sum_three_divisions += i;
        }
    }
    int get_sum() const { return sum_three_divisions; }
    int get_count() const { return counts_three_divisions; }
};

int main() {
        
    int list[] = {4, 1, 3, 6, 25, 54};

    std::cout << "[IN]: "; for (auto value : list) std::cout << value << ' ';
    std::cout << std::endl;

    CountFunctor test_functr;
    test_functr = std::for_each(list, list + sizeof(list) / sizeof(list[0]), test_functr);

    std::cout << "[OUT]: get_sum() = " << test_functr.get_sum() << "\n";
    std::cout << "[OUT]: get_count() = " << test_functr.get_count() << std::endl;

    return 0;
}