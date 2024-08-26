#include <iostream>
#include <string>
#include <Windows.h>

#include "TestLib.h"


int main() {
	
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);


    std::cout << "Введите имя: ";
    std::string usrInpt;
    std::cin >> usrInpt;
    
    GreeterLib::Greeter User1(usrInpt);
    std::cout << User1.greet();

    return 0;
}

