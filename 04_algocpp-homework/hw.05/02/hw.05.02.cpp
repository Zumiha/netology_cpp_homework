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

bool check_left_idx(int& index, int i, int size) {
    index = 2 * i + 1;

    if (index >= size) return false;
    return true;
}

bool check_right_idx(int& index, int i, int size) {
    index = 2 * i + 2;

    if (index >= size) return false;
    return true;
}

void get_parent_idx(int& index, int i) {
    index = (i - 1) / 2;
}

int main() {

    int Arr[] = { 1, 3, 6, 5, 9, 8 };
    int size = sizeof(Arr) / sizeof(Arr[0]);
 
    
    // int Arr[] = { 94, 67, 18, 44, 55, 12, 6, 42 };
    // int size = sizeof(Arr) / sizeof(Arr[0]);



    // int Arr[] = { 16, 11, 9, 10, 5, 6, 8, 1, 2, 4 };
    // int size = sizeof(Arr) / sizeof(Arr[0]);


    print_array(Arr, size);
    print_pyramid(Arr, size);   

    int a = 0;
    int b = 0;
    std::string user_input;
    
    do {
        std::cout << "Вы находитесь здесь: ";
        print_pos(Arr, b);
        std::cout << "Введите команду: ";
        std::cin >> user_input;

        if (user_input == "up") {
            if (a == 0) {
                std::cout << "Ошибка! Отсутствует родитель" << std::endl;
                b = a;
            }
            else {
                get_parent_idx(b, a);
                std::cout << "Ок" << std::endl;
                a = b;
            }
        }
        else if (user_input == "left") {
            if (check_left_idx(b, a, size) == false) {
                std::cout << "Ошибка! Отсутствует левый потомок" << std::endl;
                b = a;
            }
            else {
                std::cout << "Ок" << std::endl;
                a = b;
            }
        }
        else if (user_input == "right") {
            if (check_right_idx(b, a, size) == false) {
                std::cout << "Ошибка! Отсутствует правый потомок" << std::endl;
                b = a;
            }
            else {
                std::cout << "Ок" << std::endl;
                a = b;
            }
        }
        else if (user_input == "exit") break;
        else std::cout << "Ошибка! Неверная команда" << std::endl;

    } while (user_input != "exit");
    

    return 0;
}