#include "0_Figure.h"
#include "ValError.h"


Figure::Figure():Figure(0) {
    setName("Фигура");
}

Figure::Figure(int n) {
    setShape(n);
    setName("Фигура");
}

int Figure::getShapeCount() {
    return this->ShapeCount;
}
std::string Figure::getName() {
    return this->shapeName;
}

void Figure::displayName() {
    std::cout << this->getName() << " ";
};
void Figure::displayShapeCount() {
    std::cout << "Количество сторон: " << this->getShapeCount() << std::endl; 
};
void Figure::displaySide() {
    std::cout << "(" << "cтороны ";
    for (int i = 0; i < this->getShapeCount(); ++i) {
        std::cout << *(this->sideCntr() + i);
        (i < this->getShapeCount()-1) ? std::cout << ", " : std::cout << "; ";
    };
};
void Figure::displayAngle() {
    std::cout << "углы ";
    for (int i = 0; i < this->getShapeCount(); ++i) {
        std::cout << *(this->angleCntr() + i);
        (i < this->getShapeCount()-1) ? std::cout << ", " : std::cout << ") ";
    };
};


void Figure::printInfo() {
    displayName();
    //displayShapeCount();
    if (this->ShapeCount != 0) {
        displaySide();
        displayAngle();
        std::cout << "создан";
    }
    std::cout << std::endl;
}

const int* Figure::sideCntr() {
    return nullptr;
}
const int* Figure::angleCntr() {
    return nullptr;
}

void Figure::setName(std::string _n) {
    this->shapeName = _n;
}
void Figure::setShape(int _s) {
    this->ShapeCount = _s;
}


char sidesName[4] = { 'a', 'b', 'c', 'd' };
char anglesName[4] = { 'A', 'B', 'C', 'D' };
int ShapeCount;
std::string shapeName;