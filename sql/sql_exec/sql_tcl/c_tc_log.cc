#include "c_tc_log.h"

#include "d_sql_plugin_ref.h"
#include "../../sql_io/table.h"


TC_LOG* tc_log = nullptr;
TC_LOG* tc_log_dummy = nullptr;

int ha_commit_low(THD *thd, bool all, bool run_after_commit);

int ha_rollback_low(THD *thd, bool all);


namespace {
    bool commit_one_ht(THD *thd, plugin_ref plugin, void *arg);

    bool rollback_one_ht(THD *thd, plugin_ref plugin, void *arg);

    int set_prepared_in_tc_one_ht(THD *thd, handlerton *ht);
};

bool trx_coordinator::commit_detached_by_xid(THD *thd, bool run_after_commit) {
    auto trx_ctx = thd->get_transaction();
    auto xs = trx_ctx->xid_state();


    auto error = plugin_foreach(thd, ::commit_one_ht, MYSQL_STORAGE_ENGINE_PLUGIN,
                                const_cast<XID *>(xs->get_xid()));
    return error;
};

bool trx_coordinator::rollback_detached_by_xid(THD *thd) {
    return true;
};

bool trx_coordinator::commit_in_engines(THD *thd, bool all, bool run_after_commit) {
    return ha_commit_low(thd, all, run_after_commit);
};

bool trx_coordinator::rollback_in_engines(THD *thd, bool all) {
    return ha_rollback_low(thd, all);
};

int trx_coordinator::set_prepared_in_tc_in_engines(THD *thd, bool all) {
    int error{0};
    auto trn_ctx = thd->get_transaction();
    auto ha_list = trn_ctx->ha_trx_info(Transaction_ctx::SESSION);
    // for (auto const &ha_info : ha_list) {  // Store in SE information that
    //     // trx is prepared in TC
    //     auto ht = ha_info.ht();
    //     error = ::set_prepared_in_tc_one_ht(thd, ht);
    //     if (error != 0) return error;
    // }
    return error;
};

namespace {
    bool commit_one_ht(THD *, plugin_ref plugin, void *arg) {
        auto ht = plugin_data<handlerton *>(plugin);
        xa_status_code ret = ht->commit_by_xid(ht, static_cast<XID *>(arg));
    }
}


int TC_LOG_DUMMY::open(const char *) {
    // if (ha_recover()) {
    //     return 1;
    // }
    return 0;
}

TC_LOG::enum_result TC_LOG_DUMMY::commit(THD *thd, bool all) {
    return trx_coordinator::commit_in_engines(thd, all) ? RESULT_ABORTED: RESULT_SUCCESS;
}

int TC_LOG_DUMMY::rollback(THD *thd, bool all) {
    return trx_coordinator::rollback_in_engines(thd, all);
}

int TC_LOG_DUMMY::prepare(THD *thd, bool all) {
    return trx_coordinator::set_prepared_in_tc_in_engines(thd, all);
}

