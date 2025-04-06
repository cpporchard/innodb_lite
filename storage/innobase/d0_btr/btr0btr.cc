//
// Created by Arjun Sunil Kumar on 4/5/25.
//

#include <strings.h>
#include "../e_buf/buf0buf.h"
struct buf_block_t;

static inline buf_block_t *btr_block_get_func(
    const page_id_t &page_id, const page_size_t &page_size, ulint mode,
    ut::Location location, IF_DEBUG(const dict_index_t *index, ) mtr_t *mtr) {
    buf_block_t *block;

    block = buf_page_get_gen(page_id, page_size, mode, nullptr,
                             Page_fetch::NORMAL, location, mtr);

    if (mode != RW_NO_LATCH) {
        buf_block_dbg_add_level(block, index != nullptr && dict_index_is_ibuf(index)
                                           ? SYNC_IBUF_TREE_NODE
                                           : SYNC_TREE_NODE);
    }

    return (block);
}
