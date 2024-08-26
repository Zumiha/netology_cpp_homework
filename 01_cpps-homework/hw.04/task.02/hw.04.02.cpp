#include <iostream>

int main() {
  std::cout << "Введите целое число:\n";
  int inpNum;
  std::cin >> inpNum;
  int sumDigt = 0;
  
  while (inpNum % 10 > 0) {
    sumDigt += (inpNum % 10);
    inpNum /= 10;
  }

  std::cout << "Сумма цифр: " << sumDigt << std::endl;  
}