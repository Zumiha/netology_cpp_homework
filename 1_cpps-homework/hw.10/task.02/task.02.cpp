#include <iostream>

double* create_array (int &a) {
    return new double[a](); 
}


void display_arr (double* array, int &size) {
    std::cout << "Введённый массив: ";
     for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
}

int main() {
    std::cout << "Введите размер массива: ";
    int size;
    std::cin >> size;

    double* user_arr = create_array(size);
    display_arr (user_arr, size);

    delete[] user_arr;

    return 0;
}