#include <iostream>
#include <cassert>
#include "sql_query_builder.h"

int main () {
    SqlSelectQueryBuilder query_builder2;
    std::vector<std::string> select_columns {"name", "phone", "department"};
    query_builder2.AddColumn(select_columns);
    
    query_builder2.AddFrom("students");

    std::map<std::string,std::string> where_vals {{"id", "42"}, {"name", "John"}, {"department", "CScience"}};
    query_builder2.AddWhere(where_vals);

    assert((query_builder2.BuildQuery(), "SELECT name, phone, department FROM students WEHRE department = CScience AND id = 42 AND name = John;"));
    std::cout << "Checkpoint\n";

    return 0;
}   