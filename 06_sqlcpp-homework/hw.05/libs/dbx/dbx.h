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

enum cdParam {
    FNAME = 1, 
    LNAME = 2, 
    EMAIL = 3,
    PHONE = 4
};

namespace dbx {    
    std::string infoGraber (std::string & _filename);

    struct ClientInfo {
        ClientInfo (std::string _fname, std::string _lname, std::string _email, std::vector<std::string> _phones): first_name(_fname), last_name(_lname) , email(_email) , phones(_phones) {}
        std::string first_name;
        std::string last_name;
        std::string email;
        std::vector<std::string> phones;
        int id = -1;
    };

    class DBeditor {
    public:
        DBeditor (std::string &_filename);
        DBeditor (std::string& _host, std::string& _port, 
        std::string& _dbname, std::string& _user, std::string& _pass);
        ~DBeditor ();

        void initDBStructure();

        int addClient(const std::string& first_name, const std::string& last_name, const std::string& email);
        int addClient(ClientInfo& _client_data);
        void addPhoneNumber(const int& _client_id, const std::string& phone_num);
        void addPhoneNumber(const ClientInfo& _client_data);
        void updateClient(const int &_client_id, const std::string& _update_value, cdParam param);
        void delPhone(const int& _client_id);
        void delPhone(const int& _client_id, const std::string& phone_num);               
        void delClient (const int& _client_id);  

        pqxx::result findClient(const std::string& searchValue, cdParam param);
        void foundClients(pqxx::result& _strng);
    private:
        std::unique_ptr<pqxx::connection> conn;
    };
}
