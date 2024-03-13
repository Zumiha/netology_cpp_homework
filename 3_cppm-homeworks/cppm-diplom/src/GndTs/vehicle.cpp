#include "vehicle.h"

Transport::Transport() {
    setType(vhclType::DEF);
}
Transport::~Transport() {}

void Transport::raceEst() {

}


void Transport::setType (vhclType a) {
    this->type = a;
}
void Transport::setName (std::string call)  {
    this->name = call;
}
void Transport::setSpeed (int velocity)   {
    this->speed = velocity;
}
void Transport::setDist (int length)  {
    this->distance = length;
}

Transport::vhclType Transport::getType() {
    return this->type;
}
std::string Transport::getName() {
    return this->name;
}
double Transport::getTime() {
    return this->finishTime;
}
int Transport::getDistance()   {
    return this->distance;
}
int Transport::getSpeed()  {
    return this->speed;
}