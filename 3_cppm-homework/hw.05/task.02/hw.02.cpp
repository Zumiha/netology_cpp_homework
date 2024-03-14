#include <iostream>
#include <sstream>

class Figure {

public:
    Figure() : Figure(0) {
        setName("Фигура");
    }
    int getShapeCount() {
        return this->ShapeCount;
    }
    std::string getName() {
        return this->shapeName;
    }

    void displayName() {
        std::cout << this->getName() << ":" << std::endl;
    };
    void displaySide() {
        std::cout << "Стороны: ";
        for (int i = 0; i < this->getShapeCount(); ++i) {
            std::cout << sidesName[i] << "=" << *(this->sideCntr() + i) << " ";
        };
        std::cout << std::endl;
    };
    void displayAngle() {
        std::cout << "Углы: ";
        for (int i = 0; i < this->getShapeCount(); ++i) {
            std::cout << anglesName[i] << "=" << *(this->angleCntr() + i) << " ";
        };
        std::cout << "\n" << std::endl;
    };


    virtual void printInfo() {
        displayName();
        displaySide();
        displayAngle();
    }

    virtual const int* sideCntr() {
        return nullptr;
    }
    virtual const int* angleCntr() {
        return nullptr;
    }


protected:
    Figure(int n) {
        setShape(n);
        setName("Фигура");
    }

    void setName(std::string _n) {
        this->shapeName = _n;
    }
    void setShape(int _s) {
        this->ShapeCount = _s;
    }


private:
    char sidesName[4] = { 'a', 'b', 'c', 'd' };
    char anglesName[4] = { 'A', 'B', 'C', 'D' };
    int ShapeCount;
    std::string shapeName;

};


class Triangle : public Figure {
public:
    Triangle(int a, int b, int c, int A, int B, int C) : Figure(tri) {
        setSides(a, b, c);
        setAngles(A, B, C);

        setShape(tri);

        setName("Треугольник");
    }

private:
    void setSides(int a, int b, int c) {
        this->triSide[0] = a;
        this->triSide[1] = b;
        this->triSide[2] = c;
    }

    void setAngles(int A, int B, int C) {
        this->triAngle[0] = A;
        this->triAngle[1] = B;
        this->triAngle[2] = C;
    }

    const int* sideCntr() override {
        return this->triSide;
    }

    const int* angleCntr() override {
        return this->triAngle;
    }

    int tri = 3;
    int triSide[3] = {};
    int triAngle[3] = {};
};

class RightTriangle : public Triangle {
public:
    RightTriangle(int a, int b, int c, int A, int B) : Triangle(a, b, c, A, B, 90) {
        setName("Прямоугольный треугольник");
    }
};

class IsoTriangle : public Triangle {
public:
    IsoTriangle(int ac, int b, int AC, int B) : Triangle(ac, b, ac, AC, B, AC) {
        setName("Равнобедренный треугольник");
    }
};

class EquiTriangle : public Triangle {
public:
    EquiTriangle(int a) : Triangle(a, a, a, 60, 60, 60) {
        setName("Равносторонний треугольник");
    }
};

class Quadrilateral : public Figure {
public:
    Quadrilateral(int a, int b, int c, int d, int A, int B, int C, int D) : Figure(tetra) {
        setSides(a, b, c, d);
        setAngles(A, B, C, D);

        setShape(tetra);

        setName("Четырехугольник");
    }

private:
    void setSides(int a, int b, int c, int d) {
        this->tetraSide[0] = a;
        this->tetraSide[1] = b;
        this->tetraSide[2] = c;
        this->tetraSide[3] = d;
    }

    void setAngles(int A, int B, int C, int D) {
        this->tetraAngle[0] = A;
        this->tetraAngle[1] = B;
        this->tetraAngle[2] = C;
        this->tetraAngle[3] = D;
    }

    const int* sideCntr() override {
        return this->tetraSide;
    }

    const int* angleCntr() override {
        return this->tetraAngle;
    }

    int tetra = 4;
    int tetraSide[4] = {};
    int tetraAngle[4] = {};
};

class Parallelogram : public Quadrilateral {
public:
    Parallelogram(int a, int b, int A, int B) : Quadrilateral(a, b, a, b, A, B, A, B) {
        setName("Параллелограмм");
    }
};

class Rhombus : public Parallelogram {
public:
    Rhombus(int abcd, int AC, int BD) : Parallelogram(abcd, abcd, AC, BD) {
        setName("Ромб");
    }
};

class Rectangle : public Parallelogram {
public:
    Rectangle(int a, int b) : Parallelogram(a, b, 90, 90) {
        setName("Прямоугольник");
    }
};

class Square : public Rectangle {
public:
    Square(int a) : Rectangle(a, a) {
        setName("Квадрат");
    }
};


int main()
{
    setlocale(LC_ALL, "Russian");

    Figure* f;

    Triangle triAngle_1(10, 20, 30, 50, 60, 70);
    RightTriangle triAngle_2(10, 20, 30, 40, 50);
    IsoTriangle triAngle_3(10, 20, 50, 60);
    EquiTriangle triAngle_4(30);

    f = &triAngle_1; f->printInfo();
    f = &triAngle_2; f->printInfo();
    f = &triAngle_3; f->printInfo();
    f = &triAngle_4; f->printInfo();

    // triAngle_1.printInfo();
    // triAngle_2.printInfo();
    // triAngle_3.printInfo();
    // triAngle_4.printInfo();

    Quadrilateral tetrAngle_1(10, 20, 30, 40, 50, 60, 70, 80);
    Rectangle tetrAngle_2(10, 20);
    Square tetrAngle_3(20);
    Parallelogram tetrAngle_4(20, 30, 30, 40);
    Rhombus tetrAngle_5(30, 30, 40);

    f = &tetrAngle_1; f->printInfo();
    f = &tetrAngle_2; f->printInfo();
    f = &tetrAngle_3; f->printInfo();
    f = &tetrAngle_4; f->printInfo();
    f = &tetrAngle_5; f->printInfo();


    // tetrAngle_1.printInfo();
    // tetrAngle_2.printInfo();
    // tetrAngle_3.printInfo();
    // tetrAngle_4.printInfo();
    // tetrAngle_5.printInfo();

    return 0;
}