#include <iostream>
#include <Windows.h>

#include "dbx.h"

int main() {

	try {
        IniParser parser("dbinfo.ini");
		std::string section_name = "NetoDB";
        // std::cout << "host = "<< parser.getValue<std::string>(section_name + ".host") << std::endl;
        // std::cout << "port = " << parser.getValue<std::string>(section_name + ".port") << std::endl;
        // std::cout << "dbname = " << parser.getValue<std::string>(section_name + ".dbname") << std::endl;
		// std::cout << "user = " << parser.getValue<std::string>(section_name + ".user") << std::endl;
        // std::cout << "password = " << parser.getValue<std::string>(section_name + ".password") << std::endl;

		std::string host, port, dbname, user, pass;
		
		host = parser.getValue(section_name, "host");
   		port = parser.getValue(section_name, "port"); 
   		dbname = parser.getValue(section_name, "dbname");
   		user = parser.getValue(section_name, "user"); 
   		pass = parser.getValue(section_name, "password");	

		std::cout << "Connecting to DB...\n";
		dbx::DBeditor db = dbx::DBeditor(host, port, dbname, user, pass); 
		dbx::ClientInfo cInfo; 
		// auto a = db.addClient("testJoe6", "testSmith6", "test@6");
		// std::cout << typeid(a).name() << " " << a << std::endl;
		// db.addPhone("1");
		// db.delPhone("1");
		// db.updtClient("1");
		// db.delClient("1");

		// auto clients_info = db.findClient();
		// db.foundClients(clients_info);		

	} catch (const std::exception& e) {
		std::cerr << "\n" << e.what() << std::endl;
	}

	std::cout << "Connection Session Completed." << std::endl;

	return 0;
}