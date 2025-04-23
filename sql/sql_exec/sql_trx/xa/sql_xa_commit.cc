#include "sql_xa_commit.h"
#include "../c_tc_log.h"
#include "../b_handler.h"

class THD;

int ha_commit_trans(THD *thd, bool all, bool ignore_global_read_lock = false);

bool Sql_cmd_xa_commit::execute(THD *thd) {
    bool st = trans_xa_commit(thd);
    return st;
}

bool Sql_cmd_xa_commit::trans_xa_commit(THD *thd) {
    // if (!xid_state->has_same_xid(this->m_xid)) {
    //     return this->process_detached_xa_commit(thd);
    // }
    return this->process_attached_xa_commit(thd);
}

bool Sql_cmd_xa_commit::process_attached_xa_commit(THD *thd) const {
    if (m_xa_opt == XA_ONE_PHASE) {
        int r = ha_commit_trans(thd, true);
    } else {
        tc_log->commit(thd, /* all */ true);
    }
    return true;
}
