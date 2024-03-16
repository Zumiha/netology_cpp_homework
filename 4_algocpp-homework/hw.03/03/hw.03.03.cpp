#include <iostream>

void count_sort(int* arr, int size) {
	
	int max = arr[0];
	
	for (int i = 0; i < size; i++) {
		if (arr[i] > max) max = arr[i];
	}

	int tempSize = max + 1;
	int* tempArr = new int[tempSize] {};

	for (int i = 0; i < size; i++) {
		tempArr[arr[i]]++;
	}

	int arrIndex = 0;
	for (int i = 0; i < tempSize; i++) {
		for (int j = 0; j < tempArr[i]; j++) {
			arr[arrIndex++] = i;
		}
	}

	delete[] tempArr;
}

void dispSort(int* arr, int size) {
    std::cout << "Исходный массив:";
    for (int i = 0; i < size; ++i) {std::cout << " " << arr[i];}
    std::cout << std::endl;

    count_sort(arr, size);
    std::cout << "Отсортированный массив:";
    for (int i = 0; i < size; ++i) {std::cout << " " << arr[i];}
    std::cout << std::endl << std::endl;
}

int main(int argc, char** argv) {

    int Arr1[] = { 19, 14, 22, 22, 17, 22, 13, 21, 20, 24, 18, 10, 17, 16, 17, 20, 22, 11, 20, 16, 14, 13, 10, 22, 18, 14, 16, 24, 19, 17 };
	int Arr2[] = { 16, 17, 14, 20, 22, 20, 17, 22, 16, 19, 23, 24, 20, 22, 21, 18, 14, 16, 17, 21, 10, 11, 19, 23, 11, 11, 17, 17, 11, 21, 17, 11, 17, 16, 12, 11, 16, 22, 23, 16 };
	int Arr3[] = { 21, 15, 19, 18, 23, 12, 18, 18, 19, 23, 12, 20, 15, 22, 21, 18, 19, 20, 12, 16, 20, 14, 17, 13, 10, 23, 19, 14, 10, 22, 19, 12, 24, 23, 22, 15, 13, 22, 18, 18, 11, 23, 24, 17, 10 };

    int sizeArr1 = sizeof(Arr1) / sizeof(Arr1[0]);
    dispSort(Arr1, sizeArr1);

    int sizeArr2 = sizeof(Arr2) / sizeof(Arr2[0]);
    dispSort(Arr2, sizeArr2);

    int sizeArr3 = sizeof(Arr3) / sizeof(Arr3[0]);
    dispSort(Arr3, sizeArr3);

    return 0;
}