//
// Created by Arjun Sunil Kumar on 4/12/25.
//

#ifndef TRX0UNDO_H
#define TRX0UNDO_H

/** Transaction undo log memory object; this is protected by the undo_mutex
in the corresponding transaction object */

struct trx_undo_t {
    /** Undo log may could be allocated to store transaction GTIDs. */
    enum class Gtid_storage {
        /* No storage is allocated for GTID. */
        NONE,
        /* Storage is allocated for commit GTID. */
        COMMIT,
        /* Storage is allocated for both prepare and commit GTID. For external
        XA transaction, we have GTID fr both prepare and commit. */
        PREPARE_AND_COMMIT
    };
};

/** The transaction handle

Normally, there is a 1:1 relationship between a transaction handle
(trx) and a session (client connection). One session is associated
with exactly one user transaction. There are some exceptions to this:

* For DDL operations, a subtransaction is allocated that modifies the
data dictionary tables. Lock waits and deadlocks are prevented by
acquiring the dict_operation_lock before starting the subtransaction
and releasing it after committing the subtransaction.

* The purge system uses a special transaction that is not associated
with any session.

* If the system crashed or it was quickly shut down while there were
transactions in the ACTIVE or PREPARED state, these transactions would
no longer be associated with a session when the server is restarted.

A session may be served by at most one thread at a time. The serving
thread of a session might change in some MySQL implementations.
Therefore we do not have std::this_thread::get_id() assertions in the code.

Normally, only the thread that is currently associated with a running
transaction may access (read and modify) the trx object, and it may do
so without holding any mutex. The following are exceptions to this:

* trx_rollback_resurrected() may access resurrected (connectionless)
transactions while the system is already processing new user
transactions. The trx_sys->mutex prevents a race condition between it
and lock_trx_release_locks() [invoked by trx_commit()].

* Print of transactions may access transactions not associated with
the current thread. The caller must be holding trx_sys->mutex and
exclusive global lock_sys latch.

* When a transaction handle is in the trx_sys->mysql_trx_list or
trx_sys->trx_list, some of its fields must not be modified without
holding trx_sys->mutex exclusively.

* The locking code (in particular, deadlock checking and implicit to
explicit conversion) will access transactions associated to other
connections. The locks of transactions are protected by lock_sys latches
and sometimes by trx->mutex.

* Killing of asynchronous transactions. */

/** Represents an instance of rollback segment along with its state variables.*/
struct trx_undo_ptr_t {
};

#endif //TRX0UNDO_H
