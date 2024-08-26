#include <iostream>

int** create_two_dim_array (int &row, int &col) {
    int** array = new int*[row]();
    for (int i = 0; i < row; i ++) {
        array[i] = new int[col]();
    }
    return array; 
}

void fill_two_dim_array (int** array, int &row, int &col) {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            array[i][j] = (i+1)*(j+1);
        }
    }
}

void print_two_dim_array (int** array, int &row, int &col) {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            std::cout << array[i][j] << "\t";
        }
        std::cout << std::endl << std::endl;    
    }     
}

void delete_two_dim_array (int** array, int &row) {
    for (int i = 0; i < row; i++) {
        delete[] array[i];
    }
delete[] array;
}

int main() {

    std::cout << "Введите количество строк: ";
    int rows;
    std::cin >> rows;
    std::cout << "Введите количество столбцов: ";
    int cols;
    std::cin >> cols;

    int** user_arr = create_two_dim_array(rows, cols);
    fill_two_dim_array(user_arr, rows, cols);
    print_two_dim_array(user_arr, rows, cols);
    delete_two_dim_array(user_arr, rows);
    
    return 0;
}