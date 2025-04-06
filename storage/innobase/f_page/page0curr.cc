//
// Created by Arjun Sunil Kumar on 4/5/25.
//

#include "page0cur.h"
#include "page0page.h"
struct buf_block_t;

/** Sets the cursor object to point before the first user record
 on the page. */
static inline void page_cur_set_before_first(
    const buf_block_t *block, /*!< in: index page */
    page_cur_t *cur) /*!< in: cursor */
{
    // cur->block = (buf_block_t *) block;
    // cur->rec = page_get_infimum_rec(buf_block_get_frame(cur->block));
}

