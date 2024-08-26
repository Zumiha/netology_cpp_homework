#include <iostream>
#include <Windows.h>

class smart_array{
    private:
        int curr_size = 0;
        int full_size = 0;
        int* array = NULL;

    public:

        smart_array(const smart_array&) = delete;
        smart_array& operator=(const smart_array&) = delete;

        smart_array(int n){
            if (n < 1){
                throw std::runtime_error("Недопустимый размер создаваемого умного массива!\n");
            }
            array = new int[n]();
            curr_size = 0;
            full_size = n;
        }

        ~smart_array(){
            delete[] array;
            array = nullptr;
        }

        void add_element(int value){
            if (curr_size < full_size){
                this->array[curr_size] = value;
                ++curr_size;                   
    		} else {
                throw std::runtime_error("Превышен размер умного массива для добавления элементов!\n");
            }
         
        }

        int get_element(int n){
            if (n < 0 || n > full_size - 1){
                throw std::runtime_error("Недопустимый индекс при обращении к элементу массива!\n");
		    }
		    return this->array[n];
        }
};

int main(){
    setlocale(LC_ALL, "Russian");

    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        arr.add_element(14);
        arr.add_element(15);
        std::cout << arr.get_element(1) << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
	return 0;
}