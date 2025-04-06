//
// Created by Arjun Sunil Kumar on 4/6/25.
//

#include "btr0pcur.h"
#include "../b0_trx/trx0trx.h"
struct mtr_t;

void btr_cur_open_at_index_side(bool from_left, dict_index_t *index,
                                ulint latch_mode, btr_cur_t *cursor,
                                ulint level, ut::Location location,
                                mtr_t *mtr) {

}
