//
// Created by Arjun Sunil Kumar on 5/8/25.
//

#ifndef A_PARSE_TREE_NODES_H
#define A_PARSE_TREE_NODES_H
#include "z_mysql_sqlcommand.h"
#include "z_sql_cmd.h"
#include "sql_dml/sql_dql/a2_sql_show.h"


struct MY_SQL_PARSER_LTYPE {};

using POS = MY_SQL_PARSER_LTYPE;


template <typename Context>
class Parse_tree_node_tmpl {
};

struct Parse_context {
};

typedef Parse_tree_node_tmpl<Parse_context> Parse_tree_node;



class Parse_tree_root {
protected:
    Parse_tree_root() = default;
    explicit Parse_tree_root(const POS &pos) : m_pos(pos) {}
    virtual ~Parse_tree_root() = default;
public:
    POS m_pos;
    virtual Sql_cmd *make_cmd(THD *thd) = 0;
};

class PT_show_base : public Parse_tree_root {
protected:
    PT_show_base(const POS &pos, enum_sql_command sql_command): Parse_tree_root(pos), m_sql_command(sql_command) {}
public:
    enum_sql_command m_sql_command;
};


class PT_show_processlist final : public PT_show_base {
public:
    PT_show_processlist(const POS &pos, bool verbose)
        : PT_show_base(pos, SQLCOM_SHOW_PROCESSLIST), m_sql_cmd() {
    }

    Sql_cmd *make_cmd(THD *thd);

private:
    Sql_cmd_show_processlist m_sql_cmd;
};


#endif //A_PARSE_TREE_NODES_H