class CyclicArray {
  private:
    uint16_t* commands;
    int* values;
    int capacity;
    int next_index;

  public:
    CyclicArray(int  s): capacity(s), next_index(0), commands(new uint16_t[s]()), values(new int[s]()){}
    ~CyclicArray(){
      delete[] commands;
      delete[] values;
    }
    CyclicArray(const CyclicArray&) = delete;
    CyclicArray& operator=(const CyclicArray&) = delete;

    void push_back(int value) {
      commands[next_index] = value;   
      next_index = (next_index + 1) % capacity;
    }
    void reset_input() {
      for (int i = 0; i < capacity; ++i) {
        commands[i] = 0;
        values[i] = 0;
      }
      this->next_index = 0;
    }

    int* head() { return commands; }
    int* tail() { return commands + capacity; }
    const int* head() const { return commands; }
    const int* tail() const { return commands + capacity; }

    int get_capacity() const { return capacity; }
    int array_size() const { return capacity; }

    uint16_t& operator[](size_t pos) {
        // if(pos >= capacity) throw ("Invalid index");
        return commands[pos];
    }

    void convertToValue() {
      for (int i = 0; i < capacity; i++) {
        switch (commands[i]) {
          case 104:
            values[i] = 0;
            break;
          case 48:
            values[i] = 1;
            break;
          case 24:
            values[i] = 2;
            break;
          case 122:
            values[i] = 3;
            break;
          case 16:
            values[i] = 4;
            break;
          case 56:
            values[i] = 5;
            break;
          case 90:
            values[i] = 6;
            break;
          case 66:
            values[i] = 7;
            break;
          case 74:
            values[i] = 8;
            break;
          case 82:
            values[i] = 9;
            break;
          default:
            break;
        }
      }
    }

    int valueServo() {
      this->convertToValue();
      long long result = 0; 
      for (int i = 0; i < capacity; ++i) {
        result = result * 10 + values[i]; // Умножаем на 10 и добавляем новый элемент
      } //мы знаем что у нас значения от 0 до 9, поэтому используем упрощенный алгоритм
      return result; 
    }

    uint16_t current() {
      return commands[next_index-1];
    }
};