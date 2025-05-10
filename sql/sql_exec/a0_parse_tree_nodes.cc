//
// Created by Arjun Sunil Kumar on 5/8/25.
//


#include "a0_parse_tree_nodes.h"

#include "a1_sql_lex.h"
#include "../sql_exec/b0_sql_class.h"


Sql_cmd *PT_show_processlist::make_cmd(THD *thd) {
    LEX *lex = thd->lex;
    lex->sql_command = m_sql_command;

    return nullptr;
    // return &m_sql_cmd;
}
