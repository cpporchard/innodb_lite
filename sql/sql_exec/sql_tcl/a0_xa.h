//
// Created by Arjun Sunil Kumar on 4/22/25.
//

#ifndef XA_H
#define XA_H

// #include "sql_io/a2_table.h"
#include "../../my_alloc.h"
#include "../../sql_list.h"

class THD;

typedef struct xid_t {
} XID;


/** X/Open XA distributed transaction status codes */
enum xa_status_code {
    /**
      normal execution
    */
    XA_OK = 0,

    /**
      asynchronous operation already outstanding
    */
    XAER_ASYNC = -2,

    /**
      a resource manager error  occurred in the transaction branch
    */
    XAER_RMERR = -3,

    /**
      the XID is not valid
    */
    XAER_NOTA = -4,

    /**
      invalid arguments were given
    */
    XAER_INVAL = -5,

    /**
      routine invoked in an improper context
    */
    XAER_PROTO = -6,

    /**
      resource manager unavailable
    */
    XAER_RMFAIL = -7,

    /**
      the XID already exists
    */
    XAER_DUPID = -8,

    /**
      resource manager doing work outside transaction
    */
    XAER_OUTSIDE = -9
};

class XID_STATE {
public:
    enum xa_states {
        XA_NOTR = 0,
        XA_ACTIVE,
        XA_IDLE,
        XA_PREPARED,
        XA_ROLLBACK_ONLY
    };

    XID m_xid;
    bool m_is_detached = false;
    XID *get_xid() { return &m_xid; }

    void start_normal_xa(const XID *xid) {
        // assert(m_xid.is_null());
        // xa_state = XA_ACTIVE;
        // m_xid.set(xid);
        // m_is_detached = false;
        // rm_error = 0;
    }

    void start_detached_xa(const XID *xid, bool binlogged_arg = false) {
        // xa_state = XA_PREPARED;
        // m_xid.set(xid);
        // m_is_detached = true;
        // rm_error = 0;
        // m_is_binlogged = binlogged_arg;
    }

    bool is_detached() const { return m_is_detached; }

    bool xa_trans_rolled_back();

    bool check_has_uncommitted_xa() const;

    bool check_in_xa(bool report_error) const;
};

/*
  Structure to hold list of database_name.table_name.
  This is used at both mysqld and storage engine layer.
*/
struct st_handler_tablename {
  const char *db;
  const char *tablename;
};


typedef struct st_xarecover_txn {
  XID id;
  List<st_handler_tablename> *mod_tables;
} XA_recover_txn;


class Recovered_xa_transactions {
public:
  bool add_prepared_xa_transaction(XA_recover_txn const *prepared_xa_trn);
  bool recover_prepared_xa_transactions();
private:
  Recovered_xa_transactions();
  static Recovered_xa_transactions *m_instance;
  // std::list<XA_recover_txn *, Malloc_allocator<XA_recover_txn *>> m_prepared_xa_trans;
  bool m_mem_root_inited;
  MEM_ROOT m_mem_root;
};


bool is_xa_prepare(THD *thd);
bool is_xa_rollback(THD *thd);


#endif //XA_H
