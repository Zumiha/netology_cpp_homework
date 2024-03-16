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


int* append_to_dynamic_array(int* Arr, int& logical_size, int& actual_size, int _add_val) {
  
    if (logical_size < actual_size) {
        Arr[logical_size] = _add_val;
        logical_size++;
        return Arr;
    }
    else {
        actual_size *= 2;
        int* temp_Arr = new int[actual_size];
        for (int i = 0; i < logical_size; i++) {
            temp_Arr[i] = Arr[i];
        }
        delete[] Arr;
        temp_Arr[logical_size] = _add_val;
        logical_size++;
        return temp_Arr;
    }
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
    
    int new_val;
    while (true) {
        std::cout << "Введите элемент для добавления: ";
        std::cin >> new_val;
        if (new_val != 0) {
            Arr = append_to_dynamic_array(Arr, logical_size, actual_size, new_val);
            std::cout << "Динамический массив:";
            print_dynamic_array(Arr, logical_size, actual_size);
        }
        else break;
    }
    std::cout << "Спасибо!Ваш массив :"; 
    print_dynamic_array(Arr, logical_size, actual_size);
    
    delete[] Arr;
    return 0;
}
