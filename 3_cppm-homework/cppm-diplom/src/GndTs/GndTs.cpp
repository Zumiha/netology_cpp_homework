// #pragma once
#include "GndTs.h"

GndTs::GndTs() {
    setType(vhclType::GND);
    setName("наземное транспортное средство");    
}
GndTs::~GndTs() {

}

double GndTs::getTime2Pit() {
    return Time2Pit;
}

void GndTs::setPitTime(int stopNum, double time)   {
    this->PitTime[stopNum-1] = time;
    pitNumber ++;
}

void GndTs::setTime2Pit(int rest)    {
    this->Time2Pit = rest;
}

// void GndTs::setPitStop(int stops)   {
//     this->PitStops = stops;
// }


void GndTs::raceEst() {

    double FullTime = static_cast<double>(distance) / (speed);
    int movedTillPit = speed * Time2Pit;
    double numberOfPits = FullTime / Time2Pit;
    int pitCounter = static_cast<int>(numberOfPits);

    if (pitCounter == numberOfPits) {
        pitCounter -=1;
    }   

    // std::cout << pitCounter << " = сделано остановок" << std::endl;
    // std::cout << pitNumber << " = разных остановок" << std::endl;
    // std::cout << PitTime[pitNumber] << " = время остановки" << std::endl;

    int PitStop = 0;
    while (pitCounter > 0) {
        FullTime += PitTime[PitStop];
        pitCounter --;
        if (pitNumber > PitStop) {PitStop++;}
    }

    this->finishTime = FullTime;
}