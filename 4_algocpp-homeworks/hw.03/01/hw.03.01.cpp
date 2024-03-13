#include <iostream>

void merge_sort(int* arr, int size) {
    if (size == 1) { return; }

    int left_len = size / 2;
    int right_len = size - left_len;

    merge_sort(&arr[0], left_len);
    merge_sort(&arr[left_len], right_len);
    
    int i = 0, j = left_len;
    int* temp = new int[size];

    for (int k = 0; k < size; k++) {
        if (j > size-1 || i <= left_len-1 && arr[i] < arr[j]) {
            temp[k] = arr[i];
            i++;
        }
        else {
            temp[k] = arr[j];
            j++;
        }
    }
    for (int k = 0, i = 0; k < size; k++, i++) {
        arr[i] = temp[k];
    }
    delete[] temp;
}

void dispSort(int* arr, int size) {
    std::cout << "Исходный массив:";
    for (int i = 0; i < size; ++i) {std::cout << " " << arr[i];}
    std::cout << std::endl;

    merge_sort(arr, size);
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