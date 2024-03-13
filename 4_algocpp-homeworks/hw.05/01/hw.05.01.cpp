#include <iostream>
#include <cmath>

void print_array(int* arr, int size) {
    std::cout << "Исходный массив: ";
    for (int i = 0; i < size; i++) {
        std::cout << " " << arr[i];
    }
    std::cout << std::endl;
}

void print_pos(int* arr, int i) {
    std::string pos;
    if (i == 0) {
        std::cout << 0 << " root " << arr[i] << std::endl;
    }
    else {
        if (i % 2 == 0 && i != 0) pos = "right";
        if (i % 2 != 0 && i != 0) pos = "left";
        std::cout << ilogb(i+1) << " " << pos << "(" << arr[(i - 1) / 2] << ")" << " " << arr[i] << std::endl;
    }
}
void print_pyramid(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        print_pos(arr, i);
    }
    std::cout << std::endl;
}

int main() {

    int Arr1[] = { 1, 3, 6, 5, 9, 8 };
    int size1 = sizeof(Arr1) / sizeof(Arr1[0]);
    print_array(Arr1, size1);
    print_pyramid(Arr1, size1);    
    
    int Arr2[] = { 94, 67, 18, 44, 55, 12, 6, 42 };
    int size2 = sizeof(Arr2) / sizeof(Arr2[0]);
    print_array(Arr2, size2);
    print_pyramid(Arr2, size2);


    int Arr3[] = { 16, 11, 9, 10, 5, 6, 8, 1, 2, 4 };
    int size3 = sizeof(Arr3) / sizeof(Arr3[0]);
    print_array(Arr3, size3);
    print_pyramid(Arr3, size3);

    return 0;
}
