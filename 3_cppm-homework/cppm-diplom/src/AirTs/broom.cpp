#include "broom.h"

Broom::Broom(int path) {
    setName("Метла");
    setDist(path);
    setSpeed (20);
    setCoef(path);
    raceEst();
}

Broom::~Broom() {

}

void Broom::setCoef(int path)  {
    this->DistCoef = path/1000;  
}