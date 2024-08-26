#pragma once
#include "AirTs.h"

class Carpet: public AirTs {
public:
    Carpet(int distance);
    ~Carpet();

    void setCoef(int path) override;
};

