/**
Execute a query expression that may be a UNION and/or have an ordered result.

  @param thd          thread handle

  @returns false if success, true if error
*/

#include "../../../sql_exec/a1_sql_lex.h"
struct TABLE;
class Query_result;
class Item;
class THD;

bool Query_expression::execute(THD *thd) {
    return ExecuteIteratorQuery(thd);
}

bool Query_expression::optimize(THD *thd, TABLE *materialize_destination, bool finalize_access_paths) {
    return true;
}

bool Query_expression::create_iterators(THD *thd) {
    return true;
}


bool Query_expression::ExecuteIteratorQuery(THD *thd) {
    // mem_root_deque<Item *> *fields = get_field_list();
    // Query_result *query_result = this->query_result();
    //
    // if (query_result->send_result_set_metadata(thd, *fields, Protocol::SEND_NUM_ROWS | Protocol::SEND_EOF)) {
    //     return true;
    // }
    //
    // for (;;) {
    //     int error = m_root_iterator->Read();
    //
    //     if (query_result->send_data(thd, *fields)) {
    //         return true;
    //     }
    // }
    return true;
}
