#include "aSession.h"

int main()  {
    //setlocale(LC_ALL, "RUS");
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    system("cls");
    std::cout << "Добро пожаловать в гоночный симулятор!\n" << std::endl;  

    int user_input = 0;
    do {
        Transport **RacersList = new Transport* [8] ();
        int race_mode =  modeScreen(); 
        int track_length = trackLength();
        race_session(RacersList, race_mode, track_length);
        user_input = race_restart();
        for(int i = 0; i < 8; i++)
            delete RacersList[i];
        delete[] RacersList;
    } while (user_input != 2);
    
    return 0;
};
