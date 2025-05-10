//
// Created by Arjun Sunil Kumar on 5/8/25.
//

#ifndef SQL_CLASS_H
#define SQL_CLASS_H
#include "a1_sql_lex.h"
#include "../conn_handler/za_protocol.h"
#include "../sql_io/b1_table.h"

template<class Element_type>
class mem_root_deque {
};

class Locked_tables_list {
public:
    void unlock_locked_tables(THD *thd);
};


class THD {
public:
    LEX *lex;
    int killed{0};
    std::unique_ptr<Transaction_ctx> m_transaction;
    MDL_context mdl_context;
    Locked_tables_list locked_tables_list;

    Transaction_ctx *get_transaction() { return m_transaction.get(); }

    bool sql_parser();

    Protocol *get_protocol();

    void inc_sent_row_count(int i);

    bool send_result_set_row(const mem_root_deque<Item *> &row_items);
};

#endif //SQL_CLASS_H
