#include "fsp0fsp.h"

#include <cstddef>
#include <cstdint>
class page_size_t;
struct mtr_t;
struct buf_block_t;
typedef uint32_t page_no_t; /** Page number */

fseg_inode_t *fseg_inode_get(const fseg_header_t *header, space_id_t space,
                             const page_size_t &page_size, mtr_t *mtr,
                             buf_block_t **block) {
    // fseg_inode_t *inode = fseg_inode_try_get(header, space, page_size, mtr, block);
    // ut_a(inode);
    // return (inode);
    return nullptr;
}

/** Allocates a single free page from a segment. This function implements
 the intelligent allocation strategy which tries to minimize file space
 fragmentation.
@param[in,out] seg_header Segment header
@param[in] hint Hint of which page would be desirable
@param[in,out] direction If the new page is needed because of an index page
split, and records are inserted there in order, into which direction they go
alphabetically: fsp_down, fsp_up, fsp_no_dir
@param[in] has_done_reservation True if the caller has already done the
reservation for the page with fsp_reserve_free_extents, then there is no need to
do the check for this individual page
@param[in,out] mtr Mini-transaction
@param[in,out] init_mtr mtr or another mini-transaction in which the page should
be initialized. if init_mtr!=mtr, but the page is already latched in mtr, do not
initialize the page.
@retval NULL if no page could be allocated
@retval block, rw_lock_x_lock_count(&block->lock) == 1 if allocation succeeded
(init_mtr == mtr, or the page was not previously freed in mtr),
returned block is not allocated nor initialized otherwise */
buf_block_t *fseg_alloc_free_page_general(fseg_header_t *seg_header,
                                          page_no_t hint, std::byte direction,
                                          bool has_done_reservation, mtr_t *mtr,
                                          mtr_t *init_mtr) {
    fseg_inode_t *inode;

    // inode = fseg_inode_get(seg_header, space_id, page_size, mtr, &iblock);


}