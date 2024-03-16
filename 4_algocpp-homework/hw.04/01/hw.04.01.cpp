#include <iostream>

void print_dynamic_array(int* Arr, int logical_size, int actual_size) {
    for (int i = 0; i < logical_size; i++) {
        std::cout << " " << Arr[i];
    }
    for (int i = logical_size; i < actual_size; i++) {
        std::cout << " _";
    }
    std::cout << std::endl;
}


int main() {
    std::cout << "Введите фактичеcкий размер массива: ";
    int logical_size, actual_size;
    std::cin >> actual_size;
    while (true) {
        std::cout << "Введите логический размер массива: ";
        std::cin >> logical_size;
        if (logical_size > actual_size) {
            std::cout << "Ошибка!Логический размер массива не может превышать фактический!" << std::endl;
        }
        else break;
    }
    
    int* Arr = new int[actual_size]();
    for (int i = 0; i < logical_size; i++) {
        std::cout << "Введите arr[" << i << "]: ";
        std::cin >> Arr[i];
    }
    
    std::cout << "Динамический массив:";
    print_dynamic_array(Arr, logical_size, actual_size);
        
    delete[] Arr;
    return 0;
}