#include <iostream>
#include <exception>
#include <pqxx/pqxx>
#include <Windows.h>

#include "dbFileInfo.h"

class DBeditor {
public:
	DBeditor (std::string &_filename)	{
		std::string connection_info = dbconnect::FileInfo(_filename);
		conn = std::make_unique<pqxx::connection>(connection_info);
		std::cout << "Conneted to DB" << std::endl;
	}
	~DBeditor () {
		if (conn->is_open()) {
			conn->close();
			std::cout << "Disconnected" << std::endl;
		}
	}
private:
	std::unique_ptr<pqxx::connection> conn;
};

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	std::string filename = "info.txt";

	try {
		std::cout << "Connecting to DB...\n";
		DBeditor db = DBeditor(filename); 

		// pqxx::transaction tr{conn};

	} catch (const std::exception& e) {
		std::cout << "\n" << e.what() << std::endl;
	}

	std::cout << "Programm completed." << std::endl;

	return 0;
}