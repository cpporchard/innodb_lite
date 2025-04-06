//
// Created by Arjun Sunil Kumar on 4/5/25.
//


#include "btr0pcur.h"

#include "btr0btr.h"

void btr_pcur_t::move_to_next_page(mtr_t *mtr) {
    auto index = get_btr_cur()->index;
    dict_table_t *table = index->table;

    auto page = get_page();
    auto next_page_no = btr_page_get_next(page, mtr);

    //TODO: Main logic
    auto next_block =
        btr_block_get(page_id_t(block->page.id.space(), next_page_no),
                      block->page.size, mode, UT_LOCATION_HERE, index, mtr);

    auto next_page = buf_block_get_frame(next_block);


    btr_leaf_page_release(get_block(), mode, mtr);

    page_cur_set_before_first(next_block, get_page_cur());

    ut_d(page_check_dir(next_page));
}
