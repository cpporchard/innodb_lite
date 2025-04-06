#ifndef BTR0BTR_H
#define BTR0BTR_H

#include "../d0_btr/btr0pcur.h"
#include "../b0_trx/trx0trx.h"
#include "../e_buf/buf0buf.h"
#include "../e_buf/buf0buf.cc"
#include "../d0_btr/btr0btr.h"



/** Latching modes for btr_cur_search_to_nth_level(). */
enum btr_latch_mode : size_t {
    /** Search a record on a leaf page and S-latch it. */
    BTR_SEARCH_LEAF = 0,
    /** (Prepare to) modify a record on a leaf page and X-latch it. */
    BTR_MODIFY_LEAF = 1,
    /** Obtain no latches. */
    BTR_NO_LATCHES = 2,
    /** Start modifying the entire B-tree. */
    BTR_MODIFY_TREE = 33,
    /** Continue modifying the entire B-tree. */
    BTR_CONT_MODIFY_TREE = 34,
    /** Search the previous record. */
    BTR_SEARCH_PREV = 35,
    /** Modify the previous record. */
    BTR_MODIFY_PREV = 36,
    /** Start searching the entire B-tree. */
    BTR_SEARCH_TREE = 37,
    /** Continue searching the entire B-tree. */
    BTR_CONT_SEARCH_TREE = 38
};


/** @name Modes for buf_page_get_gen */
/** @{ */
enum class Page_fetch {
    /** Get always */
    NORMAL,

    /** Same as NORMAL, but hint that the fetch is part of a large scan.
    Try not to flood the buffer pool with pages that may not be accessed again
    any time soon. */
    SCAN,

    /** get if in pool */
    IF_IN_POOL,

    /** get if in pool, do not make the block young in the LRU list */
    PEEK_IF_IN_POOL,

    /** get and bufferfix, but set no latch; we have separated this case, because
    it is error-prone programming not to set a latch, and it  should be used with
    care */
    NO_LATCH,

    /** Get the page only if it's in the buffer pool, if not then set a watch on
    the page. */
    IF_IN_POOL_OR_WATCH,

    /** Like Page_fetch::NORMAL, but do not mind if the file page has been
    freed. */
    POSSIBLY_FREED,

    /** Like Page_fetch::POSSIBLY_FREED, but do not initiate read ahead. */
    POSSIBLY_FREED_NO_READ_AHEAD,
  };



static inline buf_block_t *btr_block_get_func(
    const page_id_t &page_id, const page_size_t &page_size, ulint mode,
    ut::Location location, mtr_t *mtr) {
    buf_block_t *block;

    block = buf_page_get_gen(page_id, page_size, mode, nullptr, Page_fetch::NORMAL, location, mtr);

    // if (mode != RW_NO_LATCH) {
    //     buf_block_dbg_add_level(block, index != nullptr && dict_index_is_ibuf(index)
    //                                        ? SYNC_IBUF_TREE_NODE
    //                                        : SYNC_TREE_NODE);
    // }

    return (block);
}

static inline buf_block_t *btr_block_get(const page_id_t &page_id,
                                         const page_size_t &page_size,
                                         ulint mode, ut::Location location,
                                         const dict_index_t *index,
                                         mtr_t *mtr) {
    return btr_block_get_func(page_id, page_size, mode, location, mtr);
}

#endif //BTR0BTR_H
