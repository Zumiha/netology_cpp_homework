#pragma once
#include <iostream>
#include <sstream>

class Figure {

public:
    Figure();
    Figure(int n);
    int getShapeCount();
    std::string getName();
    void displayName();
    void displayShapeCount();
    void displaySide();
    void displayAngle();

    virtual void printInfo();

    virtual const int* sideCntr();
    virtual const int* angleCntr();


protected:
    void setName(std::string _n);
    void setShape(int _s);


private:
    char sidesName[4] = { 'a', 'b', 'c', 'd' };
    char anglesName[4] = { 'A', 'B', 'C', 'D' };
    int ShapeCount;
    std::string shapeName;

};