//
// Created by Arjun Sunil Kumar on 4/6/25.
//

#ifndef TRX0SYS_H
#define TRX0SYS_H

class MVCC;

/** This is a wrapper for a std::vector of trx_rseg_t object pointers. */
class Rsegs {};

/** The transaction system central memory data structure. */
struct trx_sys_t {


    /** Multi version concurrency control manager */
    MVCC *mvcc;

    /** Vector of pointers to rollback segments. These rsegs are iterated
    and added to the end under a read lock. They are deleted under a write
    lock while the vector is adjusted. They are created and destroyed in
    single-threaded mode. */
    Rsegs rsegs;

    /** Vector of pointers to rollback segments within the temp tablespace;
    This vector is created and destroyed in single-threaded mode so it is not
    protected by any mutex because it is read-only during multi-threaded
    operation. */
    Rsegs tmp_rsegs;

};

#endif //TRX0SYS_H
