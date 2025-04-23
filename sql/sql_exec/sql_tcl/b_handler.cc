#include "b_handler.h"

#include "c_tc_log.h"


#define MYSQL_TABLE_IO_WAIT(OP, INDEX, RESULT, PAYLOAD) PAYLOAD


int b_handler::ha_rnd_init(bool scan) {
    return rnd_init(scan);
}

int b_handler::ha_rnd_next(uchar *buf) {
    int result;
    result = rnd_next(buf);

    // // Set status for the need to update generated fields
    // m_update_generated_read_fields = table->has_gcol();
    //
    // MYSQL_TABLE_IO_WAIT(PSI_TABLE_FETCH_ROW, MAX_KEY, result, { result = rnd_next(buf); })
    // if (!result && m_update_generated_read_fields) {
    //     result = update_generated_read_fields(buf, table);
    //     m_update_generated_read_fields = false;
    // }

    return result;
}

int b_handler::ha_extra(enum ha_extra_function operation) {
    return extra(operation);
}

int ha_commit_low(THD *thd, bool all, bool run_after_commit) {
    return 0;
}
int ha_rollback_low(THD *thd, bool all) {
    return 0;
}

int ha_rollback_trans(THD *thd, bool all) {
    int error = 0;
    return 0;
}

int ha_commit_trans(THD *thd, bool all, bool ignore_global_read_lock) {
    int error = 0;
    Transaction_ctx *trn_ctx = thd->get_transaction();
    Transaction_ctx::enum_trx_scope trx_scope = all ? Transaction_ctx::SESSION : Transaction_ctx::STMT;

    auto ha_info = trn_ctx->ha_trx_info(trx_scope);
    XID_STATE *xid_state = trn_ctx->xid_state();

    error = tc_log->prepare(thd, all);

    if (!error) {
        error = tc_log->commit(thd, all);
    }

    if (error) {
        ha_rollback_trans(thd, all);
        return 1;
    }
    trn_ctx->cleanup(); // free transaction resources
    return 0;
}


