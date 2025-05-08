//
// Created by Arjun Sunil Kumar on 5/8/25.
//

#ifndef A2_SQL_SHOW_H
#define A2_SQL_SHOW_H
#include "../../z_mysql_sqlcommand.h"
#include "a1_sql_select.h"


/// Represents SHOW PROCESSLIST statement.

class Sql_cmd_show : public Sql_cmd_select {
public:
    Sql_cmd_show(enum_sql_command sql_command);
};

class Sql_cmd_show_processlist : public Sql_cmd_show {
public:
    Sql_cmd_show_processlist() : Sql_cmd_show(SQLCOM_SHOW_PROCESSLIST) {}
};

#endif //A2_SQL_SHOW_H
