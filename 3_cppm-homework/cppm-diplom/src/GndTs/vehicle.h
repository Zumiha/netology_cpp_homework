#pragma once
#include <iostream>
#include <string>

class Transport {
public:
    enum vhclType
    {
        DEF = 0,
        GND,    // Наземный тип
        AIR,    // Воздушный тип
    };

    Transport();
    ~Transport();


    vhclType getType();
    std::string getName();
	double getTime();

    void setType (vhclType a);
    void setName (std::string call);
    void setSpeed (int velocity);
    void setDist (int length);

    virtual void raceEst();

    int getDistance();
    int getSpeed();

protected:
    vhclType type; 
    std::string name = "фэнтезийное транспортное средство";
	int speed = 10;
    int distance = 10;
    double finishTime = 1; 
};