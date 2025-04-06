//
// Created by Arjun Sunil Kumar on 4/5/25.
//


#include "ha_innodb.h"


/** Initialize a table scan.
@param[in]      scan    whether this is a second call to rnd_init()
                        without rnd_end() in between
@return 0 or error number */
int ha_innobase::rnd_init(bool scan) {
    int err = change_active_index(table_share->primary_key);

    /* Don't use semi-consistent read in random row reads (by position).
    This means we must disable semi_consistent_read if scan is false */

    if (!scan) {
        m_prebuilt->row_read_type = ROW_READ_WITH_LOCKS;
    }

    m_start_of_scan = true;
    return err;
}

int ha_innobase::rnd_next(uchar *buf) {
    error = general_fetch(buf, ROW_SEL_NEXT, 0);
}

/** Reads the next or previous row from a cursor, which must have previously
 been positioned using index_read.
 @return 0, HA_ERR_END_OF_FILE, or error number */

int ha_innobase::general_fetch(
    uchar *buf,      /*!< in/out: buffer for next row in MySQL
                     format */
    uint direction,  /*!< in: ROW_SEL_NEXT or ROW_SEL_PREV */
    uint match_mode) /*!< in: 0, ROW_SEL_EXACT, or
                     ROW_SEL_EXACT_PREFIX */ {

    if (!intrinsic) {
        ret = row_search_mvcc(buf, PAGE_CUR_UNSUPP, m_prebuilt, match_mode,
                              direction);

    } else {
        ret = row_search_no_mvcc(buf, PAGE_CUR_UNSUPP, m_prebuilt, match_mode,
                                 direction);
    }
}