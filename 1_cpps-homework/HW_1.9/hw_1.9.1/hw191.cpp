#include <iostream>

void print (int* arr, int &size){
  for (int i = 0; i < size; i++){
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
  return;  
}

int main(){
  int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int size = sizeof arr1 / sizeof arr1[0];
  print (arr1, size);
  
  int arr2[] = {6, 5, 4, 8};
  size = sizeof arr2 / sizeof arr2[0];
  print (arr2, size);

  
  int arr3[] = {1, 4, 3, 7, 5};
  size = sizeof arr3 / sizeof arr3[0];
  print (arr3, size);
  
  return 0;
}