#include <iostream>

int main() {  
  //std::string user_inStr; - так было
  std::cout << "Введите слово: \n";
  std::string user_inStr; //по комментарию "желательно инициализировать при объявлении", имеется ввиду объявлять переменные ближе к строке их использования?
  std::cin >> user_inStr;
  std::cout << "Вы ввели: \n" << user_inStr;
  return 0;
}