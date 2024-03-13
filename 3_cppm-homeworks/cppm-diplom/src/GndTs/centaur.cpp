// #pragma once
#include "centaur.h"

Centaur::Centaur(int path) {
    setName("Кентавр");
    setSpeed (15);
    setTime2Pit(8);

    setPitTime(1,2);   
    setDist (path);
    raceEst(); 
}
Centaur::~Centaur() {

}