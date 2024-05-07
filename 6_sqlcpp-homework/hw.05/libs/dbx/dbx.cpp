#include "dbx.h"

namespace dbx {
    std::string infoGraber (std::string & _filename) {
        std::ifstream file (_filename);

        std::istream_iterator<std::string> start(file), end;
        std::vector<std::string> info_vect(start, end);
        file.close();

        std::stringstream ss;
        ss << "host="+info_vect[0] + " port=" + info_vect[1] + " dbname=" + info_vect[2] + " user=" + info_vect[3] + " password=" + info_vect[4]; 

        std::string connection_info = ss.str();
        return connection_info;
    }

    std::string infoGraber (std::string& _host, std::string& _port, std::string& _dbname, std::string& _user, std::string& _pass) {
        std::stringstream ss;
        ss << "host=" + _host + " port=" + _port + " dbname=" + _dbname + " user=" + _user + " password=" + _pass; 

        std::string connection_info = ss.str();
        return connection_info;
    }

    DBeditor::DBeditor (std::string &_filename)	{
        std::string connection_info = infoGraber(_filename);
        this->conn = std::make_unique<pqxx::connection>(connection_info);
        std::cout << "Conneted to DB" << std::endl;
    }

        DBeditor::DBeditor (std::string& _host, std::string& _port, std::string& _dbname, std::string& _user, std::string& _pass)	{
        std::string connection_info = infoGraber(_host, _port, _dbname, _user, _pass);
        this->conn = std::make_unique<pqxx::connection>(connection_info);
        std::cout << "Conneted to DB" << std::endl;
    }

    DBeditor::~DBeditor () {
        if (this->conn->is_open()) {
            this->conn->close();
            std::cout << "Disconnected" << std::endl;
        }
    }

    void DBeditor::initDBStructure() {
        std::cout << "Creating Tables...";
        pqxx::work tx(*conn);
        tx.exec(
            "CREATE TABLE IF NOT EXISTS client("
            "id SERIAL PRIMARY KEY NOT NULL, "
            "first_name VARCHAR(60) NOT NULL, "
            "last_name VARCHAR(60) NOT NULL, "
            "email VARCHAR(255) UNIQUE NOT NULL)"
        );
        tx.exec(
            "CREATE TABLE IF NOT EXISTS phones("
            "id SERIAL PRIMARY KEY, "
            "phone VARCHAR(60) UNIQUE, "
            "client_id INT NOT NULL  REFERENCES client(id))"
        );
        tx.commit();
        std::cout << "Tables created" << std::endl;
    }

    void DBeditor::addClient() {
        pqxx::work tx(*conn);
        std::string first_name, last_name, email, phone_num;
        std::cout << "Enter client's first name: ";
        std::cin >> first_name;   
        std::cout << "Enter client's last name: ";
        std::cin >> last_name;
        std::cout << "Enter client's email: ";
        std::cin >> email;

        pqxx::result id_result = tx.exec_params ("INSERT INTO client (id, first_name, last_name, email) "
            "VALUES (DEFAULT, $1, $2, $3) RETURNING id" , first_name, last_name, email);
        pqxx::field const field = id_result[0][0]; 
        /*контейнер pqxx::result это технически таблица (состоящая из рядов "pqxx::row" в которых поля "pqxx::field")
        для итерации по этому объекту используют циклы, но тут возвращаем одно поле, поэтому и обращаемся напрямую. 
        вообще конечно документация библиотеки в описательных смыслах страдает. */
        tx.commit();
        
        //значение поля из pqxx::result полученного выше получаем через .c_str() и используем как id клиента
        addPhone(field.c_str());
        std::cout << std::endl;		
    }

    void DBeditor::addPhone(const std::string& _client_id) {
        pqxx::work tx(*conn);
        std::cout << "Enter client's phone number: ";
        std::string phone_num;
        std::cin >> phone_num;
        tx.exec_params("INSERT INTO phones (client_id, phone) VALUES ($1, $2)", _client_id, phone_num);
        tx.commit();
    }

    void DBeditor::delPhone(const std::string& _client_id) {
        std::cout << "Delete all client's phones? (y/n): ";
        std::string user_input;
        std::cin >> user_input;
        if (user_input != "n") {
            pqxx::work tx(*conn);
            tx.exec_params("DELETE FROM phones WHERE client_id = $1", _client_id);
            tx.commit();	
        } else {
            std::cout << "Input phone to delete: ";
            std::cin >> user_input;
            try {
                pqxx::work tx(*conn);
                tx.exec_params("DELETE FROM phones WHERE phone = $1", user_input);
                tx.commit();
            }
            catch(const std::exception& e) {
                std::cerr << e.what() << '\n';
            }			 
        }
        std::cout << std::endl;
    }

    void DBeditor::updtClient(const std::string& _client_id) {
        try {
            pqxx::work tx(*conn);
            std::cout << "Enter client's new information (or enter 'skip' to keep old info)" << std::endl;
            std::string user_input;
            std::cout << "Enter client's new first name: ";
            std::cin >> user_input;
            if (user_input != "skip") {
                tx.exec_params("UPDATE client "
                "SET first_name = $1 WHERE id = $2",
                user_input, _client_id);
            }
            std::cout << "Enter client's new last name: ";
            std::cin >> user_input;
            if (user_input != "skip") {
                tx.exec_params("UPDATE client "
                "SET last_name = $1 WHERE id = $2",
                user_input, _client_id);
            }
            std::cout << "Enter client's new email: ";
            std::cin >> user_input;
            if (user_input != "skip") {
                tx.exec_params("UPDATE client "
                "SET email = $1 WHERE id = $2",
                user_input, _client_id);
            }
            std::cout << "Enter client's new phone: ";
            std::cin >> user_input;
            if (user_input != "skip") {
                tx.exec_params("DELETE FROM phones WHERE client_id = $1", _client_id);
                tx.exec_params("INSERT INTO phones "
                "(client_id, phone) VALUES ($2, $1)",
                user_input, _client_id);
            }		
            tx.commit();
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
        std::cout << std::endl;
    }

    void DBeditor::delClient (const std::string& _client_id) {
        try {
            pqxx::work tx(*conn);
            tx.exec_params("DELETE FROM phones WHERE client_id = $1", _client_id);
            tx.exec_params("DELETE FROM client WHERE id = $1", _client_id);
            tx.commit();
        } 
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    pqxx::result DBeditor::findClient() {
        pqxx::result result;
        try {
            int input;
            std::cout << "What data do you want to search for a client?" << std::endl;
            std::cout << "1) first name" << std::endl;
            std::cout << "2) last name" << std::endl;
            std::cout << "3) email" << std::endl;
            std::cout << "4) phone number" << std::endl;
            std::cout << "\nInput: ";
            std::cin >> input;
            std::cout << std::endl;

            if (input < 1 || input > 4) {
                std::cout << "invalid input " << std::endl;
                return result;
            }

            std::string info_input;
            std::cout << "Enter information to search client: ";
            std::cin >> info_input;
                    
            pqxx::work tx(*conn);

            if (input == 4) {
                std::cout << "Searching phones...\n";

                result = tx.exec("SELECT c.id, first_name, last_name, email, p.phone  FROM client c "
                "FULL OUTER JOIN phones p ON client_id  = c.id "
                "WHERE p.phone LIKE '%" + info_input + "%' "
                "GROUP BY c.id, p.phone "
                "ORDER BY c.id ASC ");

            } else if (input == 1) {
                std::cout << "Searching names...\n";
                
                result = tx.exec("SELECT c.id, first_name, last_name, email, p.phone  FROM client c "
                "FULL OUTER JOIN phones p ON client_id  = c.id "
                "WHERE first_name LIKE '%" + info_input + "%' "
                "GROUP BY c.id, p.phone "
                "ORDER BY c.id ASC ");

            }  else if (input == 2) {
                std::cout << "Searching names...\n";
                
                result = tx.exec("SELECT c.id, first_name, last_name, email, p.phone  FROM client c "
                "FULL OUTER JOIN phones p ON client_id  = c.id "
                "WHERE last_name LIKE '%" + info_input + "%' "
                "GROUP BY c.id, p.phone "
                "ORDER BY c.id ASC ");
                
            }  else if (input == 3) {
                std::cout << "Searching email...\n";
                
                result = tx.exec("SELECT c.id, first_name, last_name, email, p.phone  FROM client c "
                "FULL OUTER JOIN phones p ON client_id  = c.id "
                "WHERE email LIKE '%" + info_input + "%' "
                "GROUP BY c.id, p.phone "
                "ORDER BY c.id ASC ");
                
            }
            tx.commit();	
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
        return result;
    }

    void DBeditor::foundClients(pqxx::result& _strng) {
        std::cout << "Client search rusults\nid\tName\tSurname\tEmail\t\tPhone number" << std::endl;
        for (auto row = _strng.begin(); row != _strng.end(); row++) {
            for (auto field = row.begin(); field != row.end(); field++) {
                std::cout << field->c_str()<< '\t';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
