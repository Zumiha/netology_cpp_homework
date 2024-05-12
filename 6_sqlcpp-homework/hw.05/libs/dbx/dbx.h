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

    struct ClientInfo {
        int id;
        std::string first_name;
        std::string last_name;
        std::string email;
        std::vector<std::string> phones;
    };

    class DBeditor {
    public:
        DBeditor (std::string &_filename);
        DBeditor (std::string& _host, std::string& _port, 
        std::string& _dbname, std::string& _user, std::string& _pass);
        ~DBeditor ();

        void initDBStructure();

        int addClient(const std::string& first_name, const std::string& last_name, const std::string& email);
        void addPhoneNumber(const int& _client_id, const std::string& phone_num);
        void updateClient(const int& _client_id, const std::string& first_name, const std::string& last_name, const std::string& email);
        void delPhone(const int& _client_id);
        void delPhone(const int& _client_id, const std::string& phone_num);               
        void delClient (const int& _client_id);  

        pqxx::result findClient(const std::string& searchValue, const int &param);
        void foundClients(pqxx::result& _strng);
    private:
        std::unique_ptr<pqxx::connection> conn;
    };
}
