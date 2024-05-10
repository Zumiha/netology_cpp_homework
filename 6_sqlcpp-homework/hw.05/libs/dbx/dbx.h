#pragma once
#include <iostream>
#include <Windows.h>
#include <pqxx/pqxx>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include <string>
#include <exception>

#include "IniParser.h"


namespace dbx {    
    std::string infoGraber (std::string & _filename);
    std::string infoGraber (std::string& _host, std::string& _port, 
    std::string& _dbname, std::string& _user, std::string& _pass);

    class DBeditor {
    public:
        DBeditor (std::string &_filename);
        DBeditor (std::string& _host, std::string& _port, 
        std::string& _dbname, std::string& _user, std::string& _pass);
        ~DBeditor ();

        void initDBStructure();
        void addClient();
        void addPhone(const std::string& _client_id);
        void delPhone(const std::string& _client_id);
        void updtClient(const std::string& _client_id);
        void delClient (const std::string& _client_id);
        pqxx::result findClient();
        void foundClients(pqxx::result& _strng);    
    private:
        std::unique_ptr<pqxx::connection> conn;
    };
}
