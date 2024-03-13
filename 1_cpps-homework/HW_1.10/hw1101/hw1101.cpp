#include <iostream>

int* create_array (int &a) {
    return new int[a](); 
}

void fill_arr (int* array, int &size) {
    int val;
    for(int i = 0; i < size; i++) {
        std::cout << "arr[" << i << "] = ";
        std::cin >> array[i];
    }
}

void display_arr (int* array, int &size) {
    std::cout << "Введённый массив: ";
     for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
}

int main() {
    std::cout << "Введите размер массива: ";
    int size;
    std::cin >> size;
    
    int* user_arr = create_array(size);
    fill_arr (user_arr, size);
    display_arr (user_arr, size);

    delete[] user_arr;

    return 0;
}