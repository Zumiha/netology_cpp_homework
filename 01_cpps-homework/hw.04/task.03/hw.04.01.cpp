#include <iostream>

int main() {
  std::cout << "Введите целое число:\n";
  int inNumbr;
  std::cin >> inNumbr;

  for (int i = 1; i <= 10; i++) {
    std::cout << inNumbr << " x " << i << " = " << i*inNumbr << "\n";
  }    
}