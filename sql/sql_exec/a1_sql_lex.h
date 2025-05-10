//
// Created by Arjun Sunil Kumar on 5/4/25.
//

#ifndef SQL_LEX_H
#define SQL_LEX_H

#include "../sql_exec/b0_sql_class.h"
#include "a0_parse_tree_nodes.h"
#include "z_mysql_sqlcommand.h"
#include "z_sql_cmd.h"
#include "../sql_list.h"
#include "../sql_io/iterators/basic_row_iterators.h"


class Table_ref;
struct TABLE;

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

/**
  This class represents a query expression (one query block or
  several query blocks combined with UNION).
*/
class Query_expression {
public:
    bool optimize(THD *thd, TABLE *materialize_destination, bool finalize_access_paths);

    bool create_iterators(THD *thd);

    Query_result *query_result();

    bool ExecuteIteratorQuery(THD *thd);

    bool execute(THD *thd);

    RowIterator *m_root_iterator;

    Query_expression() {
        auto res = new TableScanIterator(nullptr, nullptr, 0, nullptr);
        m_root_iterator = res;
    }
};

struct LEX : public Query_tables_list {
public:
    List<LEX_USER> users_list;
    LEX_STRING name;
    Sql_cmd *m_sql_cmd;
    THD *thd;
    Query_expression *unit; ///< Outer-most query expression
    Table_ref *query_tables;

    bool make_sql_cmd(Parse_tree_root *parse_tree);
};

class Parser_state {
};

#endif //SQL_LEX_H
