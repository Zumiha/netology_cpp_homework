// #pragma once
#include "camel.h"

Camel::Camel(int path) {
    setName("Верблюд");
    setSpeed (10);
    setTime2Pit(30);

    setPitTime(1,5);  
    setPitTime(2,8); 
    setDist (path); 
    raceEst();
}
Camel::~Camel() {

}