#include <iostream>
#include <sstream>

class Figure {

public:
    Figure() : Figure(0) {
        setName("Фигура");
    }


    int getSidesCount() {
        return this->sidesCount;
    }
    std::string getName() {
        return this->name;
    }

protected:
    Figure(int n) {
        setSides(n);
    }

    void setName(std::string _n) {
        this->name = _n;
    }

    void setSides(int _s) {
        this->sidesCount = _s;
    }

private:
    int sidesCount;
    std::string name;

};


class Triangle : public Figure {
public:
    Triangle() : Figure(3) {
        setName("Треугольник");
    }
};

class Quadrangle : public Figure {
public:
    Quadrangle() : Figure(4) {
        setName("Четырехугольник");
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    std::cout << "Количество сторон:" << std::endl;

    Figure fig;
    Triangle tri;
    Quadrangle quad;

    std::cout << fig.getName() << ": " << fig.getSidesCount() << std::endl;
    std::cout << tri.getName() << ": " << tri.getSidesCount() << std::endl;
    std::cout << quad.getName() << ": " << quad.getSidesCount() << std::endl;

    return 0;
}