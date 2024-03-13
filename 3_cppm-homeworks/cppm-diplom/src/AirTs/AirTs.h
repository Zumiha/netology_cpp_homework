#pragma once
#include "vehicle.h"

class AirTs : public Transport {
public:
    AirTs();
    ~AirTs();
    virtual void setCoef(int Koef);
    double getCoef();

    virtual void raceEst(); 
    
protected:    
    double DistCoef = 1;
};