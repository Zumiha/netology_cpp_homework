#include <iostream>
#include <Windows.h>

#include "dbx.h"

int main() {
	std::string filename = "info.txt";

	try {
		std::cout << "Connecting to DB...\n";
		dbx::DBeditor db = dbx::DBeditor(filename); 
		//db.addClient;
		//db.addPhone("1");
		//db.delPhone("1");
		//db.updtClient("1");
		//db.delClient("1");

		auto clients_info = db.findClient();
		db.foundClients(clients_info);		

	} catch (const std::exception& e) {
		std::cerr << "\n" << e.what() << std::endl;
	}

	std::cout << "Connection Session Completed." << std::endl;

	return 0;
}