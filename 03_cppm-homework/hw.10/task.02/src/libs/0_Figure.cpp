#include <iostream>
#include "0_Figure.h"


Figure::Figure():Figure(0) {
    setName("Фигура");
}

int Figure::getShapeCount() {
    return this->ShapeCount;
}
std::string Figure::getName() {
    return this->shapeName;
}

void Figure::displayName() {
    std::cout << this->getName() << ":" << std::endl;
};
void Figure::displaySide() {
    std::cout << "Стороны: ";
    for (int i = 0; i < this->getShapeCount(); ++i) {
        std::cout << sidesName[i] << "=" << *(this->sideCntr() + i) << " ";
    };
    std::cout << std::endl;
};
void Figure::displayAngle() {
    std::cout << "Углы: ";
    for (int i = 0; i < this->getShapeCount(); ++i) {
        std::cout << anglesName[i] << "=" << *(this->angleCntr() + i) << " ";
    };
    std::cout << "\n" << std::endl;
};


void Figure::printInfo() {
    displayName();
    displaySide();
    displayAngle();
}

const int* Figure::sideCntr() {
    return nullptr;
}
const int* Figure::angleCntr() {
    return nullptr;
}


Figure::Figure(int n) {
    setShape(n);
    setName("Фигура");
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