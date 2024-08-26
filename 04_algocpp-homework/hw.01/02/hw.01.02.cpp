#include <iostream>

int numBigger(int *arr, int size, int cp) {
  int start = 0, end = size - 1, mid = 0, mark = 0;
  if (arr[0] > cp)
    return size;

  while ((start <= end) && (mark == 0)) {
    mid = (start + end) / 2;
    if ((arr[mid] <= cp) && (arr[mid + 1] > cp)) {
      mark = 1;
    }

    if (arr[mid] > cp) {
      end = mid - 1;
    } else {
      start = mid + 1;
    }
  }
  return (size - 1 - mid);
}

int main() {
  int size = 9;
  int arr[] = {14, 16, 19, 32, 32, 32, 56, 69, 72};
  int count_point;
  std::cout << "Введите точку отсчёта: ";
  std::cin >> count_point;
  int abc = numBigger(arr, size, count_point);
  std::cout << "Количество элементов в массиве больших, чем " << count_point << ": " << abc << std::endl;
}