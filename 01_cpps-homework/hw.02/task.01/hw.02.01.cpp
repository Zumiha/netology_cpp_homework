#include <iostream>

int main() {
  //int user_inVal; - так было
  std::cout << "Введите число: \n";
  int user_inVal;//по комментарию "желательно инициализировать при объявлении", имеется ввиду объявлять переменные ближе к строке их использования?
  std::cin >> user_inVal;
  std::cout << "Вы ввели: \n" << user_inVal;
  return 0;
}