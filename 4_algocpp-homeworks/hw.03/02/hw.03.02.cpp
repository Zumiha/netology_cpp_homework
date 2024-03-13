#include <iostream>

void quick_sort(int* arr, int size) {
    int i = 0;
    int j = size - 1;

    int pivot = arr[size / 2];

    while (i <= j) {
        while (arr[i] < pivot) { i++; }
        while (arr[j] > pivot) { j--; }
        if (i <= j) {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    if (j > 0) { quick_sort(arr, j + 1); }
    if (i < size) { quick_sort(&arr[i], size - i); }
}

void dispSort(int* arr, int size) {
    std::cout << "Исходный массив:";
    for (int i = 0; i < size; ++i) {std::cout << " " << arr[i];}
    std::cout << std::endl;

    quick_sort(arr, size);
    std::cout << "Отсортированный массив:";
    for (int i = 0; i < size; ++i) {std::cout << " " << arr[i];}
    std::cout << std::endl << std::endl;
}

int main(int argc, char** argv) {
    int Arr1[] = {3, 43, 38, 29, 18, 72, 57, 61, 2, 33};
    int Arr2[] = {88, 91, 87, 59, 53, 49, 29, 16, 4, 27, 28, 89, 2, 25, 74};
    int Arr3[] = {24, 66, 20, 79, 30, 16, 19, 62, 94, 59, 0, 7, 59, 90, 84, 60, 95, 62};

    int sizeArr1 = sizeof(Arr1) / sizeof(Arr1[0]);
    dispSort(Arr1, sizeArr1);

    int sizeArr2 = sizeof(Arr2) / sizeof(Arr2[0]);
    dispSort(Arr2, sizeArr2);

    int sizeArr3 = sizeof(Arr3) / sizeof(Arr3[0]);
    dispSort(Arr3, sizeArr3);

    return 0;
}