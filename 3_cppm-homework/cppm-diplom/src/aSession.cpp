#include "aSession.h"

int modeScreen()    {
    int temp;
    std::cout << "1. Гонка для наземного транспорта" << std::endl;
    std::cout << "2. Гонка для воздушного транспорта" << std::endl;
    std::cout << "3. Гонка для наземного и воздушного транспорта" << std::endl;
    std::cout << "Выберите тип гонки: ";
    std::cin >> temp;
    system("cls");
    return temp;
}
int trackLength()   {
    int dis_temp;
    std::cout << "Укажите длину дистанции (должна быть положительна): ";
    std::cin >> dis_temp;
    if (dis_temp < 0) trackLength();
    system("cls");
    return dis_temp;
}

void race_session (Transport* RacersList[], int race_mode, int track_length) {
    
    Transport* a_boot = new Boots (track_length);
    Transport* a_camel = new Camel (track_length);
    Transport* a_camelrace = new CamelFast (track_length);
    Transport* a_centaur = new Centaur (track_length);
    Transport* a_broom = new Broom (track_length);
    Transport* a_carpet = new Carpet (track_length);
    Transport* a_eagle = new Eagle (track_length);
    

    int user_input = 1;
    int input_object = 10;
    int racer_counter = 0;
    bool check = true;

    do {

        while (user_input != 1) {
            std::cout << "Должно быть зарегистрировано хотя бы 2 транспортных средства" << std::endl;
            std::cout << "1. Зарегистрировать транспорт" << std::endl;
            if (racer_counter > 1) {std::cout << "2. Начать гонку" << std::endl;}
            std::cout << "Выберите действие: ";
            std::cin >> user_input;
            if (user_input == 2 && racer_counter > 1) {input_object = 10; break;}
            system("cls");
        } 

        if (user_input == 2 && racer_counter > 1) {break;}

        registry_display(RacersList, race_mode, track_length);

        std::cout << "Выберите транспорт или 0 для окончания процесса регистрации: ";
        std::cin >> input_object;

        
        switch (input_object)  {
        case 1:
            if (!check_race_mode(race_mode, a_boot)) {racer_wrong_mode();break;}                
            if (check_racer_reg(RacersList, a_boot)) {racer_reg_true (a_boot);break;}
            RacersList[racer_counter] = new Boots (track_length);
            racer_counter++;
            system("cls");
            break;
        case 2:
            if (!check_race_mode(race_mode, a_broom)) {racer_wrong_mode();break;} 
            if (check_racer_reg(RacersList, a_broom)) {racer_reg_true (a_broom);break;}
            RacersList[racer_counter] = new Broom (track_length);
            racer_counter++;
            system("cls");
            break;
        case 3:
            if (!check_race_mode(race_mode, a_camel)) {racer_wrong_mode();break;} 
            if (check_racer_reg(RacersList, a_camel)) {racer_reg_true (a_camel);break;}
            RacersList[racer_counter] = new Camel (track_length);
            racer_counter++;
            system("cls");
            break;
        case 4:
            if (!check_race_mode(race_mode, a_centaur)) {racer_wrong_mode();break;} 
            if (check_racer_reg(RacersList, a_centaur)) {racer_reg_true (a_centaur);break;}
            RacersList[racer_counter] = new Centaur (track_length);
            racer_counter++;
            system("cls");
            break;
        case 5:
            if (!check_race_mode(race_mode, a_eagle)) {racer_wrong_mode();break;} 
            if (check_racer_reg(RacersList, a_eagle)) {racer_reg_true (a_eagle);break;}
            RacersList[racer_counter] = new Eagle (track_length);
            racer_counter++;
            system("cls");
            break;
        case 6:
            if (!check_race_mode(race_mode, a_camelrace)) {racer_wrong_mode();break;} 
            if (check_racer_reg(RacersList, a_camelrace)) {racer_reg_true (a_camelrace);break;}
            RacersList[racer_counter] = new CamelFast (track_length);
            racer_counter++;
            system("cls");
            break;
        case 7:
            if (!check_race_mode(race_mode, a_carpet)) {racer_wrong_mode();break;} 
            if (check_racer_reg(RacersList, a_carpet)) {racer_reg_true (a_carpet);break;}
            RacersList[racer_counter] = new Carpet (track_length);
            racer_counter++;
            system("cls");
            break;
        case 0:
            system("cls");
            user_input = 0; 
            break;
        default:
            system("cls");
            break;
        } 

    } while (check);

    // расчет гонки
    system("cls");

    race_result (RacersList, track_length); user_input = 0;

    // delete[] a_boot;
    // delete[] a_camel;
    // delete[] a_camelrace;
    // delete[] a_centaur;
    // delete[] a_broom;
    // delete[] a_carpet;
    // delete[] a_eagle;
}

int race_restart () {
    int val = 0;
    std::cout << "\n1.Провести ещё одну гонку " << std::endl;
    std::cout << "2.Выйти " << std::endl;
    std::cout << "Выберите действие: ";
    std::cin >> val;
    system("cls");
    return val;
}

void registry_display(Transport* Racerlist[], int race_mode, int race_lenght) {
    
    std::string str;
    if (race_mode == 1) str = "наземного транспорта. ";
    if (race_mode == 2) str = "воздушного транспорта. ";
    if (race_mode == 3) str = "наземного и воздушного транспорта. ";
    std::cout << "Гонка для " << str << "Расстояние: " << race_lenght <<  std::endl;

    if (Racerlist[0] != NULL)
    {
        int count=0;
        std::cout << "Зарегистрированные транспортные средства: ";
        while (Racerlist[count] != NULL)
        {
            std::cout << Racerlist[count]->getName();
            count++;
            if (Racerlist[count] != NULL) {std::cout << ", ";} else { std::cout << " ";}
        }
        std::cout << std::endl;
    }
    
    std::cout << "1. Ботинки-вездеходы\n2. Метла\n3. Верблюд\n4. Кентавр\n5. Орёл\n6. Верблюд-быстроход\n7. Ковер-самолет\n0. Закончить регистрацию " << std::endl;
}


bool check_racer_reg(Transport* Racerlist[], Transport* checker) {
    int count = 0;
    do {
        if (Racerlist[count] == NULL) {
            return false;
        } else if (Racerlist[count]->getName() == checker->getName()) {
            return true;    
        }        
        count++;
    } while (count < 7);
    return false;
}

void racer_reg_true (Transport* checker) {
    system("cls");
    std::cout << checker->getName() << " уже зарегистрирован!" << std::endl;
}

bool check_race_mode(int race_mode, Transport* checker) {
    if (race_mode == checker->getType() || race_mode == 3) {return true;}
    return false;
}

void racer_wrong_mode () {
    system("cls");
    std::cout << "Попытка зарегистрировать неправильный тип транспортного средства!" << std::endl;
}

void race_result (Transport* Racerlist[], int track_length) {
    struct result {
        std::string name;
        double time = 0.0;
    };
    result res[8]{};
    
    int counter = 0;
    while (Racerlist[counter]!=NULL) {
        res[counter].name = Racerlist[counter]->getName();
        res[counter].time = Racerlist[counter]->getTime();
        counter++;
    };
   
    result temp;
    for (int i = 0; i < counter - 1; i++) {
        for (int j = 0; j < counter - 1; j++) {
            if (res[j].time > res[j + 1].time) {
                temp = res[j];
                res[j] = res[j + 1];
                res[j + 1] = temp;
            }
        }
    }
    std::cout << "Результаты гонки: " << std::endl;
    for (int i = 0; i < counter; i++) {
        std::cout << i+1 << ". " << res[i].name << ". " << " Время: " << res[i].time << std::endl;
    }
    std::cout << std::endl;
}