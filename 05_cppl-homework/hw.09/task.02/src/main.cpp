#include "BigInt.h"

int main() {
    auto number1 = BigInt("114575");
    auto number2 = BigInt("78524");

    std::cout << "Number 1 :\t" << number1.getValue() << std::endl;
    std::cout << "Number 2 :\t" << number2.getValue() << std::endl;
    std::cout << std::endl;

    try
    {
        std::cout << "Sum of two Big Numbers" << std::endl;
        auto result = number1 + number2;
        std::cout << "Sum = " << result.getValue() << std::endl;  // 193099

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    std::cout << "\n";

    try
    {
        std::cout << "Bin Number 1 multiply by number" << std::endl;
        auto result = number1 * 10;
        std::cout << "Sum = " << result.getValue() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }    

    return 0;
}