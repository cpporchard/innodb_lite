#pragma once
#include <sys/types.h>

#include "../../sql_io/b1_table.h"





namespace trx_coordinator {
    bool commit_detached_by_xid(THD *thd, bool run_after_commit = true);
    bool rollback_detached_by_xid(THD *thd);
    bool commit_in_engines(THD *thd, bool all = false,bool run_after_commit = true);
    bool rollback_in_engines(THD *thd, bool all = false);
    int set_prepared_in_tc_in_engines(THD *thd, bool all = false);
    bool should_statement_set_prepared_in_tc(THD *thd);
};

class TC_LOG {
public:

    TC_LOG() = default;
    virtual ~TC_LOG() = default;

    enum enum_result { RESULT_SUCCESS, RESULT_ABORTED, RESULT_INCONSISTENT };
    virtual int open(const char *opt_name) = 0;
    virtual void close() = 0;
    virtual enum_result commit(THD *thd, bool all) = 0;
    virtual int rollback(THD *thd, bool all) = 0;
    virtual int prepare(THD *thd, bool all) = 0;
};

class TC_LOG_DUMMY : public TC_LOG  // use it to disable the logging
{
public:
    TC_LOG_DUMMY() = default;
    int open(const char *) override;
    void close() override {}
    enum_result commit(THD *thd, bool all) override;
    int rollback(THD *thd, bool all) override;
    int prepare(THD *thd, bool all) override;
};

// class TC_LOG_MMAP : public TC_LOG {
// public:  // only to keep Sun Forte on sol9x86 happy
//     typedef enum {
//         PS_POOL,   // page is in pool
//         PS_ERROR,  // last sync failed
//         PS_DIRTY   // new xids added since last sync
//       } PAGE_STATE;
//     uint npages, inited;
// public:
//     TC_LOG_MMAP() : inited(0) {}
//     int open(const char *opt_name) override;
//     void close() override;
//     enum_result commit(THD *thd, bool all) override;
//     int rollback(THD *thd, bool all) override;
//     int prepare(THD *thd, bool all) override;
//     int recover();
//     uint size() const;
// };


// TC_LOG *tc_log;
// TC_LOG_DUMMY tc_log_dummy;

extern TC_LOG* tc_log;
extern TC_LOG* tc_log_dummy;

// TC_LOG_MMAP tc_log_mmap;