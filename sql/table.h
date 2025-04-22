#ifndef TABLE_INCLUDED
#define TABLE_INCLUDED
#include <memory>

#include "handler.h"
#include "xa.h"
#include "iterators/basic_row_iterators.h"


class handler;

struct TABLE_SHARE {
};

struct TABLE {
    handler *file{nullptr};
    uchar * record;
};
class Ha_trx_info_list {
public:
};

class Transaction_ctx {
    XID_STATE m_xid_state;
public:
    enum enum_trx_scope { STMT = 0, SESSION };
    XID_STATE *xid_state() { return &m_xid_state; }
    Ha_trx_info_list  ha_trx_info(Transaction_ctx::enum_trx_scope session);
};

struct THD {
    int killed{0};
    std::unique_ptr<Transaction_ctx> m_transaction;
public:
    Transaction_ctx *get_transaction() { return m_transaction.get(); }
};

#endif  // TABLE_INCLUDED
