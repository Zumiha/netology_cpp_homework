#include <iostream>
#include <fstream>

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

void wr_arr_txt (int* array, int &size) {
    std::ofstream op_file ("out.txt");
    op_file << size << std::endl;
    
    for (int i = size-1; i >= 0; i--) {
        op_file << array[i] << " ";
    }
    op_file.close();
}

int main() {
    std::cout << "Введите размер массива: ";
    int size;
    std::cin >> size;
    
    int* user_arr = create_array(size);
    fill_arr (user_arr, size);
    wr_arr_txt (user_arr, size);
   
    delete[] user_arr;

    return 0;
}