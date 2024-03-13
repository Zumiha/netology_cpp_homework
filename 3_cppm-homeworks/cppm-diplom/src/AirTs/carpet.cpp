#include "carpet.h"

Carpet::Carpet(int path) {
    setName("Ковёр-самолёт");
    setDist(path);
    setSpeed (10);
    setCoef(path);
    raceEst();
}

Carpet::~Carpet() {

}

void Carpet::setCoef(int path)  {
    path < 1000 ? this->DistCoef = 0 : path < 5000 ? this->DistCoef = 3 : path < 10000 ? this->DistCoef = 10 : this->DistCoef = 5;   
}