#include "eagle.h"

Eagle::Eagle(int path) {
    setName("Орёл");
    setDist(path);
    setSpeed (8);
    setCoef(6);
    raceEst();
}

Eagle::~Eagle() {

}
