// #pragma once
#include "camelracer.h"

CamelFast::CamelFast(int path) {
    setName("Верблюд-быстроход");
    setSpeed (40);
    setTime2Pit(10);

    setPitTime(1,5);
    setPitTime(2,6.5);  
    setPitTime(3,8); 
    setDist (path); 
    raceEst();
}
CamelFast::~CamelFast() {

}