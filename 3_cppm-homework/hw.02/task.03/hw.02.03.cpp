#include <iostream>
#include <windows.h>

struct itemAdress
{
    std::string city = "default city";
    std::string street = "default street";
    int house = 0;
    int flat = 0;
    int index = 0;
};

void outputAdress(const itemAdress &fa)
{
    std::cout << "Город: " << fa.city << "\n" << "Улица: " << fa.street << "\n" << "Номер дома: " << fa.house << "\n"; 
    std::cout << "Номер квартиры: " <<  fa.flat  << "\n" << "Индекс: " << fa.index << std::endl;
}



int main()
{
    itemAdress first_adress;
    itemAdress second_adress;

    first_adress.city = "Москва";
    first_adress.street = "Арбат";
    first_adress.house = 12;
    first_adress.flat = 8;
    first_adress.index = 123456;

    second_adress.city = "Ижевск";
    second_adress.street = "Пушкина";
    second_adress.house = 59;
    second_adress.flat = 143;
    second_adress.index = 953769;

    outputAdress(first_adress);
    std::cout << std::endl;
    outputAdress(second_adress);
  
    return 0;
}