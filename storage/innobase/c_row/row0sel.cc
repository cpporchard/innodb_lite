#include <strings.h>
#include <cstddef>

#include "row0mysql.h"
#include "../d0_btr/btr0pcur.h"
#include "../b0_trx/trx0trx.h"
#include "../f_page/page0types.h"
#include "../d0_btr/btr0btr.h"
#include "../f_page/page0page.h"

#define dberr_t int
typedef unsigned char uchar;

#define UT_LOCATION_HERE (ut::Location{__FILE__, __LINE__})

dberr_t row_search_mvcc(uchar *buf, page_cur_mode_t mode,
                        row_prebuilt_t *prebuilt, ulint match_mode,
                        const ulint direction) {
    btr_pcur_t *pcur = prebuilt->pcur;
    const rec_t *rec = nullptr;

    // Start transaction context
    trx_t trx = trx_t{};
    trx_start_if_not_started(&trx, false, UT_LOCATION_HERE);

    // Open the index cursor at appropriate position
    pcur->open_at_side(mode == PAGE_CUR_G, nullptr, BTR_SEARCH_LEAF, false, 0, nullptr);

    rec_loop:
        rec = pcur->get_rec();

        if (page_rec_is_infimum(rec)) {
            goto next_rec;
        }

        if (page_rec_is_supremum(rec)) {
            goto next_rec;
        }

    next_rec:
        // Move to the next record
        if (pcur->move_to_next(nullptr)) {
            goto rec_loop;
        }

    return -1;
}
