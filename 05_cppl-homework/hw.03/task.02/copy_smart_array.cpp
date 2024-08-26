#include <iostream>
#include <Windows.h>

class smart_array{
    private:
        int* array = NULL;
        int length = 0;
        int curr_size = 0;

    public:
        smart_array(int n){
            if (n < 1){
                throw std::runtime_error("Недопустимый размер создаваемого умного массива!\n");
            }
            array = new int[n]();
            length = n;
        }

        smart_array(const smart_array& copied_array){
            this->length = copied_array.length;
            this->curr_size = copied_array.curr_size;
            this->array = new int[length]();
            for (int i = 0; i < this->curr_size; ++i){
                *(this->array + i) = *(copied_array.array + i);
            }
        }

        ~smart_array(){
            delete[] array;
            array = nullptr;
        }

        void add_element(int value){
            if (curr_size < length){
                this->array[curr_size] = value;
                ++curr_size;                   
    		} else {
                throw std::runtime_error("Превышен размер умного массива для добавления элементов!\n");
            }
         
        }

        int get_element(int n){
            if (n < 0 || n > length - 1){
                throw std::runtime_error("Недопустимый индекс при обращении к элементу массива!\n");
		    }
		    return this->array[n];
        }

        void prtArray(){
            for (int i = 0; i < curr_size; ++i)
                std::cout << *(array + i) << " ";
            std::cout << std::endl;
        }

        smart_array& operator=(const smart_array& copied_array){
            if (this == &copied_array){return *this;}
            
            delete[] this->array;
            this->array = new int[copied_array.length]();
            this->length = copied_array.length;
            this->curr_size = copied_array.curr_size;
            for (int i = 0; i < this->curr_size; ++i){
                *(this->array + i) = *(copied_array.array + i);
            }
            return *this;
        }
};

int main(){
    setlocale(LC_ALL, "Russian");

    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        // arr.prtArray();

        smart_array new_array(2);
        new_array.add_element(44); 
        new_array.add_element(34);
        // new_array.prtArray();
        // std::cout << "\n";


        // arr = new_array;
        // arr.prtArray();
        // new_array.prtArray();
        // smart_array newest_array(arr);
        // newest_array.prtArray();
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
	return 0;
}