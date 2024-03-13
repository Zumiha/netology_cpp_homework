#include <iostream>

void swap (int* x, int* y) {
  int tmp = *x;
  *x = *y;
  *y = tmp;
  return;
} 

int main() {
  int a = 5, b = 8;
  std::cout << "\na = " << a << ", b = " << b << std::endl;
  int *p_a = &a, *p_b = &b;
  swap (p_a, p_b);
  std::cout << "a = " << a << ", b = " << b << std::endl;

  return 0;
}