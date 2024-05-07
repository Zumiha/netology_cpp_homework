#include "IniParser.h"

int main() {
    try {
        IniParser parser("info.ini");

        // auto value1 = parser.getValue<double>("Section1.var1");
        // std::cout << "In Section2: var1 = " << value1 << '\n';
        // auto value2 = parser.getValue<int>("Section1.var1");
        // std::cout << "In Section2: var1 = " << value2 << '\n';
        // auto value3 = parser.getValue<std::string>("Section1.var2");
        // std::cout << "In Section2: var2 = " << value3 << '\n';


        // // auto value4 = parser.getValue<double>("Section4.Vid");
        // // std::cout << "In Section2: Vid = " << value4 << '\n';

        // // auto value5 = parser.getValue<double>("Section3.var1");
        // // std::cout << "In Section3: var1 = " << value5 << '\n';

        // auto value6 = parser.getValue<double>("Section2.var2");
        // std::cout << "In Section2: var2 = " << value6 << '\n';

        // auto value7 = parser.getValue<std::string>("Section1.var3");
        // std::cout << "In Section1: var3 = " << value7 << '\n';


        std::cout << "var1 string: "<< parser.getValue<std::string>("Section1.var1") << std::endl;
        std::cout << "var1 int: " << parser.getValue<int>("Section1.var1") << std::endl;
        std::cout << "var1 double: " << parser.getValue<double>("Section1.var1") << std::endl << std::endl;
		
		std::cout << "var2 string: " << parser.getValue<int>("Section1.var4") << std::endl;
        std::cout << "var2 double: " << parser.getValue<double>("Section1.var4") << std::endl;
        
        //parser.getValue<float>("Section1.var1"); //данная команда приводит к ошибке времени компиляции

    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}