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


namespace dbconnect {
    std::string FileInfo (std::string & _filename);
}

namespace dbx {
    class DBeditor {
    public:
        DBeditor (std::string &_filename);
        ~DBeditor ();

        void crtTables();
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
