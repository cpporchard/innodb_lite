//
// Created by Arjun Sunil Kumar on 4/22/25.
//

#ifndef XA_H
#define XA_H
typedef struct xid_t {
} XID;

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
    XID *get_xid() { return &m_xid; }
};

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


#endif //XA_H
