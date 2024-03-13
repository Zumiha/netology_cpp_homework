#include <iostream>

void print (int* arr, int &size){
  for (int i = 0; i < size; i++){
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
  return;  
}

void reverse (int* arr, int &size){
  int beg = 0, end = size - 1;
  // std::cout << beg << "\n" << size << std::endl;
  while (beg < end) {
    int temp = arr[beg];
    arr[beg] = arr[end];
    arr[end] = temp;
    beg++;
    end--;
  }
  return;  
}

int main(){
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int size = sizeof arr / sizeof arr[0];
  std::cout << "До функции reverse: ";
  print (arr, size);
  
  reverse (arr, size);
  std::cout << "После функции reverse: ";
  print (arr, size);
  
  return 0;
}