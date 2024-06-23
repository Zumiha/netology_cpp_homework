#pragma once
#include "sql_query_builder.h"

enum WhereTypeLogic {
    EQUAL,
    LESS,
    MORE
};

class AdvQueryBuilder : public SqlSelectQueryBuilder {
private:

public:
    AdvQueryBuilder() {}
    ~AdvQueryBuilder() {}

    std::string BuildQuery(WhereTypeLogic type) {
        if (this->query.from_columns.empty()) throw std::invalid_argument ("FROM field empty");
        if (this->query.where_requst_vals.empty()) throw std::invalid_argument ("WHERE fields empty");
        
        std::string logic;
        switch (type) {
            case EQUAL: logic = " = "; break;
            case LESS: logic = " < "; break;
            case MORE: logic = " > "; break;        
            default: throw std::invalid_argument ("Invalid logic operator in WHERE field"); break;
        }

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

        select_request.append("FROM ").append(this->query.from_columns).append(" WEHRE");
        {
            auto it = this->query.where_requst_vals.begin(); auto ended = this->query.where_requst_vals.end() - 1;
            for (auto smt: this->query.where_requst_vals) {
                select_request.append(" ").append(smt.first).append(logic).append(smt.second);
                if (it != ended) {select_request.append(" AND");}
                it++;
            }
        }    
        select_request.append(";");
        return select_request;
    }

};