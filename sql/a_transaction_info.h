#pragma once
#include "xa.h"

class Ha_trx_info_list {
};

class Transaction_ctx {
    XID_STATE m_xid_state;
public:
    enum enum_trx_scope { STMT = 0, SESSION };
    XID_STATE *xid_state() { return &m_xid_state; }
    Ha_trx_info_list  ha_trx_info(Transaction_ctx::enum_trx_scope session);
    void cleanup();
};