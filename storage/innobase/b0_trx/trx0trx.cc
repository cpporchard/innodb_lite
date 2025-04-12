//
// Created by Arjun Sunil Kumar on 4/6/25.
//

#include "trx0trx.h"

/** Starts the transaction if it is not yet started.
@param[in] trx Transaction
@param[in] read_write True if read write transaction */
void trx_start_if_not_started_low(trx_t *trx, bool read_write) {
}


/** Creates a transaction object for MySQL.
 @return own: transaction object */
trx_t *trx_allocate_for_mysql(void) {
    trx_t *trx;

    // trx = trx_allocate_for_background();
    //
    // trx_sys_mutex_enter();
    //
    // ut_d(trx->in_mysql_trx_list = true);
    // UT_LIST_ADD_FIRST(trx_sys->mysql_trx_list, trx);
    //
    // trx_sys_mutex_exit();

    return (trx);
}
