#include <iostream>

int main() {
  std::cout << "Оператор: ";
  std::string oper;
  std::cin >> oper;
  std::cout << std::boolalpha << '\n';

  if (oper == "||") {
    std::cout << false << "\t" << false << "\t" << (false || false) << "\n";
    std::cout << true << "\t" << false << "\t" << (true || false) << "\n";
    std::cout << false << "\t" << true << "\t" << (false || true) << "\n";
    std::cout << true << "\t" << true << "\t" << (true || true) << std::endl;
  }
  else if (oper == "&&") {
    std::cout << false << "\t" << false << "\t" << (false && false) << "\n";
    std::cout << true << "\t" << false << "\t" << (true && false) << "\n";
    std::cout << false << "\t" << true << "\t" << (false && true) << "\n";
    std::cout << true << "\t" << true << "\t" << (true && true) << std::endl;
  }
  else {std::cout<<"Неверный оператор!";} 
  
    return 0;
}