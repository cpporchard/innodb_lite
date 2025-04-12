//
// Created by Arjun Sunil Kumar on 4/11/25.
//

#include "row0sel.h"

/* Note that inside MySQL 'byte' is defined as char on Linux! */
using byte = unsigned char;

/** Does an insert for MySQL using INSERT graph. This function will run/execute
INSERT graph.
@param[in]      mysql_rec       row in the MySQL format
@param[in,out]  prebuilt        prebuilt struct in MySQL handle
@return error code or DB_SUCCESS */
static dberr_t row_insert_for_mysql_using_ins_graph(const byte *mysql_rec,
                                                    row_prebuilt_t *prebuilt) {
    dberr_t err;
    run_again:
        // row_ins_step(thr);
        // auto was_lock_wait = row_mysql_handle_errors(&err, trx, thr, &savept);
        // if (was_lock_wait) {
        //     goto run_again;
        // }

    return err;
}

/** Does an insert for MySQL.
@param[in]      mysql_rec       row in the MySQL format
@param[in,out]  prebuilt        prebuilt struct in MySQL handle
@return error code or DB_SUCCESS*/
dberr_t row_insert_for_mysql(const std::byte *mysql_rec, row_prebuilt_t *prebuilt) {
    return 0;
    // return (row_insert_for_mysql_using_ins_graph(mysql_rec, prebuilt));
}
