#include "trx0undo.h"

#include "trx0trx.h"
struct buf_block_t;
struct mtr_t;


/** Tries to add a page to the undo log segment where the undo log is placed.
@return X-latched block if success, else NULL */
buf_block_t *trx_undo_add_page(
    trx_t *trx,               /*!< in: transaction */
    trx_undo_t *undo,         /*!< in: undo log memory object */
    trx_undo_ptr_t *undo_ptr, /*!< in: assign undo log from
                              referred rollback segment. */
    mtr_t *mtr)               /*!< in: mtr which does not have
                              a latch to any undo log page;
                              the caller must have reserved
                              the rollback segment mutex */ {


    // new_block = fseg_alloc_free_page_general(
    // TRX_UNDO_SEG_HDR + TRX_UNDO_FSEG_HEADER + header_page,
    // undo->top_page_no + 1, FSP_UP, true, mtr, mtr);


}