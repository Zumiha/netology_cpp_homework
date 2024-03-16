#pragma once
#include "AirTs.h"

class Broom: public AirTs {
public:
    Broom(int distance);
    ~Broom();

    void setCoef(int path) override;
};

