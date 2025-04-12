#include "ha_innodb.h"
#include "../c_row/row0sel.h"

#define ROW_SEL_NEXT 0

ha_innobase::ha_innobase(handlerton *hton, TABLE_SHARE *table_share): handler(hton, table_share) {
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
