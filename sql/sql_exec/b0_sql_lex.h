//
// Created by Arjun Sunil Kumar on 5/4/25.
//

#ifndef SQL_LEX_H
#define SQL_LEX_H
#include "d0_mysql_sqlcommand.h"

class Query_tables_list {
public:
    enum_sql_command sql_command;
};

struct LEX : public Query_tables_list {

};
#endif //SQL_LEX_H
