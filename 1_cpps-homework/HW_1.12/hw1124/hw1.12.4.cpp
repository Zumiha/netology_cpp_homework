#include <iostream>
#include <fstream>


int** crt_2Darray (int &row, int &col) {
    int** array = new int*[row]();
    for (int i = 0; i < row; i ++) {
        array[i] = new int[col]();
    }
    return array; 
}

void prt_2Darray (int** array, int &row, int &col) {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;    
    }     
}

void del_2Darray (int** array, int &row) {
    for (int i = 0; i < row; i++) {
        delete[] array[i];
    }
delete[] array;
}

int main() {
  std::ifstream file ("in.txt");
  std::string str;

  file >> str;
  int rows = std::stoi(str);
  file >> str;
  int cols = std::stoi(str); 

  int** op_arr = crt_2Darray(rows, cols);

  for(int i = 0; i < rows; i++) {
        for(int j = cols - 1; j >= 0; j--) {
          file >> str;
          op_arr[i][j] = std::stoi(str);
        }
    }

  prt_2Darray(op_arr, rows, cols);
  del_2Darray(op_arr, rows);
    
    return 0;
}