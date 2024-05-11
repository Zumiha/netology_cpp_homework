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

    struct client_info {
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

        int addClient(const std::string& firstName, const std::string& lastName, const std::string& email);
        // void addPhoneNumber(int clientId, const std::string& phoneNumber);
        // void updateClient(int clientId, const std::string& firstName, const std::string& lastName, const std::string& email);
        // void removeClient(int clientId);
        // void findClient(const std::string& searchValue);

        void initDBStructure();

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
