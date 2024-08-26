#include <iostream>

int main()
{
  int numbr;
  int summ = 0;
  
  do {
  std::cout << "Введите целое число или число '0', чтобы закончить:\n";
  std::cin >> numbr;
  summ += numbr;    
  } while (numbr != 0);

  std::cout << "Сумма: " << summ << std::endl;  
  
}