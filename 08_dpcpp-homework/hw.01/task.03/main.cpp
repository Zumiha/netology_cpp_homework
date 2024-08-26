#include <iostream>
#include <cassert>
#include "adv_sql_query_builder.h"

int main () {
    AdvQueryBuilder query_builder3;
    std::vector<std::string> select_columns {"name", "phone"};
    query_builder3.AddColumn(select_columns);
    
    query_builder3.AddFrom("students");

    std::map<std::string,std::string> where_vals {{"id", "42"}};
    query_builder3.AddWhere(where_vals);

    assert((query_builder3.BuildQuery(MORE), "SELECT name, phone FROM students WEHRE id > 42;"));
    std::cout << "Checkpoint\n";

    return 0;
}   