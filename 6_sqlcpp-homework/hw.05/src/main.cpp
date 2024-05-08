#include <iostream>
#include <Windows.h>

#include "dbx.h"
#include "IniParser.h"

int main() {

	try {
        IniParser parser("dbinfo.ini");

        std::cout << "host = "<< parser.getValue<std::string>("NetoDB.host") << std::endl;
        std::cout << "port = " << parser.getValue<std::string>("NetoDB.port") << std::endl;
        std::cout << "dbname = " << parser.getValue<std::string>("NetoDB.dbname") << std::endl;
		std::cout << "user = " << parser.getValue<std::string>("NetoDB.user") << std::endl;
        std::cout << "password = " << parser.getValue<std::string>("NetoDB.password") << std::endl;

		//std::cout << "Connecting to DB...\n";
		//dbx::DBeditor db = dbx::DBeditor(filename); 
		//db.addClient;
		//db.addPhone("1");
		//db.delPhone("1");
		//db.updtClient("1");
		//db.delClient("1");

		//auto clients_info = db.findClient();
		//db.foundClients(clients_info);		

	} catch (const std::exception& e) {
		std::cerr << "\n" << e.what() << std::endl;
	}

	std::cout << "Connection Session Completed." << std::endl;

	return 0;
}