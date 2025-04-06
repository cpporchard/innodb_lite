//
// Created by Arjun Sunil Kumar on 4/5/25.
//

#ifndef BTR0BTR_H
#define BTR0BTR_H
#include <strings.h>

#ifndef UNIV_HOTBACKUP
struct buf_block_t;




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
