#pragma once
class Counter {

public:
    Counter();
    Counter(int _num);
    int getVal();
    int incVal();
    int decVal();

private:
    int Value;
    void setVal(int _num);

};

void cntCalc(Counter& _cntObj);