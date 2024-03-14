#pragma once 

#include <iostream>
#include <Windows.h>
#include "Ts.h"

int modeScreen();
int trackLength();

void race_session (Transport* RacersList[], int race_mode, int track_length);
int race_restart ();

void registry_display(Transport* Racerlist[], int race_mode, int race_lenght);

bool check_racer_reg(Transport* Racerlist[], Transport* checker);
void racer_reg_true(Transport* checker);

bool check_race_mode(int race_mode, Transport* checker);
void racer_wrong_mode();

void race_result (Transport* Racerlist[], int track_length);