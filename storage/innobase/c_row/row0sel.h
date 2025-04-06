#include "row0mysql.h"
#include "../d0_btr/btr0pcur.h"
#include "../b0_trx/trx0trx.h"
#include "../f_page/page0types.h"
#include "../d0_btr/btr0btr.h"
#include "../f_page/page0page.h"

#define dberr_t int
typedef unsigned char uchar;

#ifndef ROW0SEL_H
#define ROW0SEL_H

[[nodiscard]] dberr_t row_search_mvcc(uchar *buf, page_cur_mode_t mode,
                                      row_prebuilt_t *prebuilt,
                                      ulint match_mode, const ulint direction);

#endif //ROW0SEL_H
