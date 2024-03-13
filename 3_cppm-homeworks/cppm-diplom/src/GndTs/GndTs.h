#pragma once
#include "vehicle.h"

class GndTs : public Transport {
public:
    GndTs();
    ~GndTs();

    void setTime2Pit(int nonstop);
    void setPitTime(int stopNum, double time);

    void raceEst() override;

    double getTime2Pit();
    
protected:
    double Time2Pit = 10;
    double PitTime[3] = {};
    int pitNumber = -1;
};