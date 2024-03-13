#pragma once
#include <iostream>

class Figure {

public:
    Figure();
    int getShapeCount();
    std::string getName();
    void displayName();
    void displaySide();
    void displayAngle();

    virtual void printInfo();

    virtual const int* sideCntr();
    virtual const int* angleCntr();


protected:
    Figure(int n);
    void setName(std::string _n);
    void setShape(int _s);


private:
    char sidesName[4] = { 'a', 'b', 'c', 'd' };
    char anglesName[4] = { 'A', 'B', 'C', 'D' };
    int ShapeCount;
    std::string shapeName;

};