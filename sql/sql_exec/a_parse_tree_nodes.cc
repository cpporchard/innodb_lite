//
// Created by Arjun Sunil Kumar on 5/8/25.
//


#include "a_parse_tree_nodes.h"

#include "b0_sql_lex.h"
#include "../sql_io/table.h"


Sql_cmd *PT_show_processlist::make_cmd(THD *thd) {
    LEX *lex = thd->lex;
    lex->sql_command = m_sql_command;

    return nullptr;
    // return &m_sql_cmd;
}
