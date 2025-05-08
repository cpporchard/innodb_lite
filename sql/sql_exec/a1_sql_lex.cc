//
// Created by Arjun Sunil Kumar on 5/8/25.
//

#include "a1_sql_lex.h"

#include "a0_parse_tree_nodes.h"
/**
  Uses parse_tree to instantiate an Sql_cmd object and assigns it to the Lex.

  @param parse_tree The parse tree.

  @returns false on success, true on error.
*/
bool LEX::make_sql_cmd(Parse_tree_root *parse_tree) {
    m_sql_cmd = parse_tree->make_cmd(thd);
    return false;
}
