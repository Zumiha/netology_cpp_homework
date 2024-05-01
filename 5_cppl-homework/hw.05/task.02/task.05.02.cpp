#include <iostream>

template <class T>
class table {
private:
    int rows = 0;
    int cols = 0;
    T** matrix;

public:
    table (T rows_, T cols_) : rows(rows_), cols(cols_){
        if ((this->rows >= 0) && (this->cols >= 0)) {
            matrix = new T * [this->rows];
            for (int i = 0; i < this->rows; i++) {
                matrix[i] = new T[this->cols]{};
            }
        } else { throw std::logic_error("Table dimentions incorrect"); }
    }

    table(const table& copied_table){
        this->rows = copied_table.getRows();
        this->cols = copied_table.getRows();
        this->matrix = new int[this->rows]();
        for (int i = 0; i < this->rows; ++i){
            *(this->matrix + i) = *(copied_table.matrix + i);
        }
    }

    ~table(){
        for (int i = 0; i < this->rows; i++) {
            delete[] this->matrix[i];
        }
        delete [] this->matrix; 
    }

    const int getRows() const {
        return this->rows;
    }

    const int getCols() const {
        return this->cols;
    }

    table& operator=(const table& copied_table){
        if (this == &copied_table){return *this;}
        
        for (int i = 0; i < this->rows; i++) {
            delete[] this->matrix[i];
        }
        delete [] this->matrix; 

        this->rows = copied_table.getRows();
        this->cols = copied_table.getRows();
        this->matrix = new int[copied_table.getRows()]();

        for (int i = 0; i < this->curr_size; ++i){
            *(this->matrix + i) = *(copied_table.matrix + i);
        }
        return *this;
    }

    auto & operator[](size_t index) {
        if (index >= this->rows || index >= this->cols || index < 0 ) {
            throw(std::logic_error("Adressing outside table limits"));
        }
    return matrix[index];
    };

    const auto & operator[](size_t index) const {
        if (index >= this->rows || index >= this->cols || index < 0 ) {
            throw(std::logic_error("Adressing outside table limits"));
        }
    return matrix[index];
    };

    const T getSize(){
        return rows*cols;
    }


};

int main () {

    try {
        auto test = table <int> (2, 3);
        test[0][0] = 4;
        std::cout << test[0][0];
        // std::cout << "\ntable size: " << test.getSize() << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}