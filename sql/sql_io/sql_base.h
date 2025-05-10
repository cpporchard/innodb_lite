//
// Created by Arjun Sunil Kumar on 4/11/25.
//

#ifndef SQL_BASE_H
#define SQL_BASE_H
#include "a_table.h"

class Prelocking_strategy {
};

class Table_ref {
};

class Open_table_context {
public:
    enum enum_open_table_action {
        OT_NO_ACTION = 0,
        OT_BACKOFF_AND_RETRY,
        OT_REOPEN_TABLES,
        OT_DISCOVER,
        OT_REPAIR,
        OT_FIX_ROW_TYPE
      };
};

bool open_tables_for_query(THD *thd, Table_ref *tables, int flags);

#endif //SQL_BASE_H
