// #pragma once
#include "boots.h"

Boots::Boots(int path) {
    setName("Ботинки-вездеходы");
    setSpeed (6);
    setTime2Pit(60);

    setPitTime(1,10);  
    setPitTime(2,5); 
    setDist (path); 
    raceEst();
}
Boots::~Boots() {

}