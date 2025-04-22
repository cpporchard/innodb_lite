#include "ha_innodb.h"
#include "../c_row/row0sel.h"

#define ROW_SEL_NEXT 0

trx_t *trx_allocate_for_mysql(void) ;

ha_innobase::ha_innobase(handlerton *hton, TABLE_SHARE *table_share): b_handler(hton, table_share) {
    // Constructor logic
}

ha_innobase::~ha_innobase() {
}

/** Stores a row in an InnoDB database, to the table specified in this
 handle.
 @return error code */

int ha_innobase::write_row(uchar *record) /*!< in: a row in MySQL format */ {
    dberr_t error;
    // trx_t *trx = thd_to_trx(m_user_thd);
    // TrxInInnoDB trx_in_innodb(trx);

    /* Prepare INSERT graph that will be executed for actual INSERT (This is a one time operation) */
    // if (m_prebuilt->mysql_template == nullptr || m_prebuilt->template_type != ROW_MYSQL_WHOLE_ROW) {
    //     /* Build the template used in converting quickly between
    //     the two database formats */
    //
    //     build_template(true);
    // }

    /* Execute insert graph that will result in actual insert. */
    // error = row_insert_for_mysql((std::byte *)record, m_prebuilt);
}

int ha_innobase::rnd_init(bool scan) {
    // int err = change_active_index(table_share->primary_key);
    //
    // /* Don't use semi-consistent read in random row reads (by position).
    // This means we must disable semi_consistent_read if scan is false */
    //
    // if (!scan) {
    //     m_prebuilt->row_read_type = ROW_READ_WITH_LOCKS;
    // }
    //
    // m_start_of_scan = true;
    // return err;
    return 0;
}

int ha_innobase::rnd_next(uchar *buf) {
    return general_fetch(buf, ROW_SEL_NEXT, 0);
}

int ha_innobase::general_fetch(
    uchar *buf,
    uint direction,
    uint match_mode) {
    auto prebuilt = row_prebuilt_t{};
    prebuilt.pcur = new btr_pcur_t{};
    return row_search_mvcc(buf, PAGE_CUR_UNSUPP, &prebuilt, match_mode, direction);
}

/** Obtain the InnoDB transaction of a MySQL thread.
@param[in,out]  thd     MySQL thread handler.
@return reference to transaction pointer */

[[nodiscard]] trx_t *&thd_to_trx(THD *thd) {
    // innodb_session_t *&innodb_session = thd_to_innodb_session(thd);
    // ut_ad(innodb_session != nullptr);
    //
    // return (innodb_session->m_trx);
}

/** Allocates an InnoDB transaction for a MySQL handler object for DML.
 @return InnoDB transaction handle */
trx_t *innobase_trx_allocate(THD *thd) /*!< in: user thread handle */ {
    trx_t *trx;
    trx = trx_allocate_for_mysql();

    return trx;
}


/** Gets the InnoDB transaction handle for a MySQL handler object, creates
 an InnoDB transaction struct if the corresponding MySQL thread struct still
 lacks one.
 @return InnoDB transaction handle */
trx_t *check_trx_exists(THD *thd) /*!< in: user thread handle */ {
    trx_t *&trx = thd_to_trx(thd);
    if (trx == nullptr) {
        trx = innobase_trx_allocate(thd);
    }
}


/** Updates the user_thd field in a handle and also allocates a new InnoDB
 transaction handle if needed, and updates the transaction fields in the
 m_prebuilt struct. */
void ha_innobase::update_thd(THD *thd) /*!< in: thd to use the handle */ {

    trx_t *trx = check_trx_exists(thd);
    // TrxInInnoDB trx_in_innodb(trx);



}



/** Updates the user_thd field in a handle and also allocates a new InnoDB
 transaction handle if needed, and updates the transaction fields in the
 m_prebuilt struct. */

void ha_innobase::update_thd() {
    // THD *thd = ha_thd();
    // update_thd(thd);
}


/** Tells something additional to the handler about how to do things.
 @return 0 or error number */
int ha_innobase::extra(enum ha_extra_function operation) {
    update_thd();

    switch (operation) {
        case HA_EXTRA_FLUSH:
            break;
    };
    return 0;
}
