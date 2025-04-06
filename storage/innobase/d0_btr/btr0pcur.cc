//
// Created by Arjun Sunil Kumar on 4/5/25.
//


#include "btr0pcur.h"
#include "btr0btr.h"
#define UT_LOCATION_HERE (ut::Location{__FILE__, __LINE__})

void btr_pcur_t::move_to_next_page(mtr_t *mtr) {
    auto index = get_btr_cur()->index;
    auto page = get_page();
    auto next_page_no = 0;
    auto mode = 0;

    auto next_block =  //<--- Core Logic
        btr_block_get(page_id_t(0, next_page_no),page_size_t{}, mode, UT_LOCATION_HERE, index, mtr);

    // auto next_page = buf_block_get_frame(next_block);
    //
    //
    // btr_leaf_page_release(get_block(), mode, mtr);
    //
    // page_cur_set_before_first(next_block, get_page_cur());
    //
    // ut_d(page_check_dir(next_page));
}
