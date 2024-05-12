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
		dbx::ClientInfo test_client_1{"test75", "tost75", "test@tost75", {"78911995","888522569","88117756"}}; 
		
		auto a = db.addClient("testJoe9", "testSmith9", "test@9");
		db.addPhoneNumber(a, "766654224424");

		db.addClient(test_client_1);
		db.addPhoneNumber(test_client_1);
				
		db.addPhoneNumber(8, "655477755");
		db.delPhone(8, "655477755");


		db.updateClient(8, "test@8updated", EMAIL);
		// db.delClient(2);

		auto clients_info = db.findClient("Joe", FNAME);
		db.foundClients(clients_info);		

	} catch (const std::exception& e) {
		std::cerr << "\n" << e.what() << std::endl;
	}

	std::cout << "Connection Session Completed." << std::endl;

	return 0;
}