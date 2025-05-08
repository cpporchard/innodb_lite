//
// Created by Arjun Sunil Kumar on 5/4/25.
//

#ifndef SQL_LEX_H
#define SQL_LEX_H
#include "z_mysql_sqlcommand.h"
#include "z_sql_cmd.h"
#include "../sql_list.h"

struct MYSQL_LEX_STRING {
    char *str;
    int length;
};

struct LEX_USER;
typedef struct MYSQL_LEX_STRING LEX_STRING;

class Query_tables_list {
public:
    enum_sql_command sql_command;
};

struct LEX : public Query_tables_list {
    List<LEX_USER> users_list;
    LEX_STRING name;
    Sql_cmd *m_sql_cmd;
};

class Parser_state {
};

#endif //SQL_LEX_H
