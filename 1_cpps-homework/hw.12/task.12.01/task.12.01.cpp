#include <iostream>
#include <fstream>

int main() {
  std::ifstream file ("in.txt");
  std::string str;

  file >> str;
  int size = std::stoi(str);    
  int* arr = new int[size]();

  for (int i = size-1; i >= 0; i--) {
    file >> str;
    arr[i] = stoi(str);
  }

  for (int i = 0; i < size; i++) {
    std::cout << arr[i] << " ";
  }

  delete[] arr;
  
  return 0;
}

