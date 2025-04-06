#include "ha_innodb.h"
#include "../c_row/row0sel.h"

#define ROW_SEL_NEXT 0

ha_innobase::ha_innobase(handlerton *hton, TABLE_SHARE *table_share): handler(hton, table_share) {
    // Constructor logic
}

ha_innobase::~ha_innobase() {

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
    return row_search_mvcc(buf, PAGE_CUR_UNSUPP, nullptr, match_mode, direction);
}
