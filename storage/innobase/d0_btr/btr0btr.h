#ifndef BTR0BTR_H
#define BTR0BTR_H

struct buf_block_t;

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


/** Gets a buffer page and declares its latching order level.
@param page_id Tablespace/page identifier
@param page_size Page size
@param mode Latch mode
@param[in]      location  Location from where this method is called.
@param index Index tree, may be NULL if not the insert buffer tree
@param mtr Mini-transaction handle
@return the block descriptor */
static inline buf_block_t *btr_block_get(const page_id_t &page_id,
                                         const page_size_t &page_size,
                                         ulint mode, ut::Location location,
                                         const dict_index_t *index,
                                         mtr_t *mtr) {
    return btr_block_get_func(page_id, page_size, mode, location,
                              IF_DEBUG(index, ) mtr);
}

#endif //BTR0BTR_H
