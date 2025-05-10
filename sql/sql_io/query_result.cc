//
// Created by Arjun Sunil Kumar on 5/9/25.
//

/* Send data to client. Returns 0 if ok */

#include "query_result.h"

#include "c1_item.h"
#include "../sql_exec/b0_sql_class.h"

class Protocol;
class THD;

bool Query_result_send::send_data(THD *thd,const mem_root_deque<Item *> &items) {
    Protocol *protocol = thd->get_protocol();

    protocol->start_row();
    if (thd->send_result_set_row(items)) {
        protocol->abort_row();
        return true;
    }

    thd->inc_sent_row_count(1);
    return protocol->end_row();
}
