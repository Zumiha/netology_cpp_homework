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

    DBeditor::DBeditor (std::string &_filename)	{
        std::string connection_info = infoGraber(_filename);
        this->conn = std::make_unique<pqxx::connection>(connection_info);
        std::cout << "Conneted to DB" << std::endl;
    }

    DBeditor::DBeditor (std::string& _host, std::string& _port, std::string& _dbname, std::string& _user, std::string& _pass)	{
        std::stringstream ss;
        ss << "host=" + _host + " port=" + _port + " dbname=" + _dbname + " user=" + _user + " password=" + _pass; 
        std::string connection_info = ss.str();

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

    int DBeditor::addClient(const std::string& first_name, const std::string& last_name, const std::string& email) {
        pqxx::work tx(*conn);

        pqxx::result id_result = tx.exec_params ("INSERT INTO client (id, first_name, last_name, email) "
            "VALUES (DEFAULT, $1, $2, $3) RETURNING id" , first_name, last_name, email);
        pqxx::field const field = id_result[0][0]; 
        int val = std::stoi(field.c_str()); 
        /* контейнер pqxx::result это технически таблица (состоящая из рядов "pqxx::row" в которых поля "pqxx::field")
        для итерации по этому объекту используют циклы, но тут возвращаем одно поле, поэтому и обращаемся напрямую. 
        вообще конечно документация библиотеки в описательных смыслах страдает. */
        tx.commit();        
        //значение поля из pqxx::result полученного выше получаем через .c_str() и используем как id клиента
        return val;
    }

    void DBeditor::addPhoneNumber(const int& _client_id, const std::string& phone_num) {
        pqxx::work tx(*conn);
        tx.exec_params("INSERT INTO phones (client_id, phone) VALUES ($1, $2)", _client_id, phone_num);
        tx.commit();
    }

    void DBeditor::updateClient(const int& _client_id, const std::string& first_name, const std::string& last_name, const std::string& email) {
        try {
            pqxx::work tx(*conn);
            if (first_name != "skip") {
                tx.exec_params("UPDATE client "
                "SET first_name = $1 WHERE id = $2",
                first_name, _client_id);
            }

            if (last_name != "skip") {
                tx.exec_params("UPDATE client "
                "SET last_name = $1 WHERE id = $2",
                last_name, _client_id);
            }

            if (email != "skip") {
                tx.exec_params("UPDATE client "
                "SET email = $1 WHERE id = $2",
                email, _client_id);
            }
            tx.commit();
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void DBeditor::delPhone(const int& _client_id) {
        pqxx::work tx(*conn);
        tx.exec_params("DELETE FROM phones WHERE client_id = $1", _client_id);
        tx.commit();
    }
    void DBeditor::delPhone(const int& _client_id, const std::string& phone_num) {
        pqxx::work tx(*conn);
        tx.exec_params("DELETE FROM phones WHERE client_id = $1 AND phone = $2", _client_id, phone_num);
        tx.commit();
    }    

    void DBeditor::delClient (const int& _client_id) {
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

    pqxx::result DBeditor::findClient(const std::string& searchValue, const int &param) {
        pqxx::result result;
        pqxx::work tx(*conn);
        
        switch (param)
        {
        case 1: //first name
            result = tx.exec("SELECT c.id, first_name, last_name, email, p.phone  FROM client c "
                "FULL OUTER JOIN phones p ON client_id  = c.id "
                "WHERE first_name LIKE '%" + searchValue + "%' "
                "GROUP BY c.id, p.phone "
                "ORDER BY c.id ASC ");
            break;
        case 2: //last name
            result = tx.exec("SELECT c.id, first_name, last_name, email, p.phone  FROM client c "
                "FULL OUTER JOIN phones p ON client_id  = c.id "
                "WHERE last_name LIKE '%" + searchValue + "%' "
                "GROUP BY c.id, p.phone "
                "ORDER BY c.id ASC ");
            break;
        case 3: //email
            result = tx.exec("SELECT c.id, first_name, last_name, email, p.phone  FROM client c "
                "FULL OUTER JOIN phones p ON client_id  = c.id "
                "WHERE email LIKE '%" + searchValue + "%' "
                "GROUP BY c.id, p.phone "
                "ORDER BY c.id ASC ");
            break;
        case 4: //phone number
            result = tx.exec("SELECT c.id, first_name, last_name, email, p.phone  FROM client c "
                "FULL OUTER JOIN phones p ON client_id  = c.id "
                "WHERE p.phone LIKE '%" + searchValue + "%' "
                "GROUP BY c.id, p.phone "
                "ORDER BY c.id ASC ");
            break;
        default:
            throw std::invalid_argument("Error. Invalid <client_data> parameter.\n");
            break;
        }
        std::cout << "Searching " + param = 1 ? "first names…" : param = 2 ? "last names…" : param = 3 ? "email…" : param = 4 ? "phone…" : "unknown..." << std::endl;
        tx.commit();	
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
