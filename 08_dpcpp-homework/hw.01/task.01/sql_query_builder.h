#include <string>
#include <vector>
#include <stdexcept>

struct SqlSelectQuery {
    std::vector<std::string> select_columns{};
    std::string from_columns{};
    std::vector<std::pair<std::string, std::string>> where_requst_vals{};     
};


class SqlSelectQueryBuilder {
private:
    SqlSelectQuery query;
    std::string select_request{};
public:
    SqlSelectQueryBuilder() {}
    ~SqlSelectQueryBuilder() {}

    SqlSelectQueryBuilder& AddColumn(const std::string column) {
        this->query.select_columns.push_back(column);
        return *this;
    }
    SqlSelectQueryBuilder& AddFrom(const std::string from_val) {
        if (!this->query.from_columns.empty()) {
            this->query.from_columns.clear();
        }
        this->query.from_columns.append(from_val);
        return *this;
    }
    SqlSelectQueryBuilder& AddWhere(const std::string key, const std::string value) {
        this->query.where_requst_vals.push_back(std::make_pair(key,value));
        return *this;
    }
    std::string BuildQuery() {
        if (this->query.from_columns.empty()) throw std::invalid_argument ("FROM field empty");
        if (this->query.where_requst_vals.empty()) throw std::invalid_argument ("WHERE fields empty");
        std::string select_request{};
        select_request.append("SELECT ");
        if (this->query.select_columns.empty()) {select_request.append("* ");}
        else {
            auto ended = this->query.select_columns.end() - 1;
            for (auto it = this->query.select_columns.begin(); it != this->query.select_columns.end(); it++) {
                select_request.append(*it);
                it != ended ? select_request.append(", ") : select_request.append(" ");
            }
        }

        select_request.append("FROM ").append(this->query.from_columns).append(" WEHRE ");
        {
            auto it = this->query.where_requst_vals.begin(); auto ended = this->query.where_requst_vals.end() - 1;
            for (auto smt: this->query.where_requst_vals) {
                select_request.append(" ").append(smt.first).append(" = ").append(smt.second);
                if (it != ended) {select_request.append(" AND");}
                it++;
            }
        }    
        select_request.append(";");
        return select_request;
    }
};