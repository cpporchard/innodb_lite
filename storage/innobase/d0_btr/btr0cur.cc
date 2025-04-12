//
// Created by Arjun Sunil Kumar on 4/6/25.
//

#include "btr0btr.h"
#include "btr0pcur.h"
#include "../b0_trx/trx0trx.h"
struct upd_t;
struct big_rec_t;
struct dtuple_t;
struct que_thr_t;
struct mtr_t;
/** Operation type flags used in trx_undo_report_row_operation */
constexpr uint32_t TRX_UNDO_INSERT_OP = 1;

void btr_cur_open_at_index_side(bool from_left, dict_index_t *index,
                                ulint latch_mode, btr_cur_t *cursor,
                                ulint level, ut::Location location,
                                mtr_t *mtr) {
}

/** Writes information to an undo log about an insert, update, or a delete
 marking of a clustered index record. This information is used in a rollback of
 the transaction and in consistent reads that must look to the history of this
 transaction.
 @return DB_SUCCESS or error code */
dberr_t trx_undo_report_row_operation(
    ulint flags, /*!< in: if BTR_NO_UNDO_LOG_FLAG bit is
                             set, does nothing */
    ulint op_type, /*!< in: TRX_UNDO_INSERT_OP or
                             TRX_UNDO_MODIFY_OP */
    que_thr_t *thr, /*!< in: query thread */
    dict_index_t *index, /*!< in: clustered index */
    const dtuple_t *clust_entry, /*!< in: in the case of an insert,
                             index entry to insert into the
                             clustered index, otherwise NULL */
    const upd_t *update, /*!< in: in the case of an update,
                             the update vector, otherwise NULL */
    ulint cmpl_info, /*!< in: compiler info on secondary
                             index updates */
    const rec_t *rec, /*!< in: in case of an update or delete
                             marking, the record in the clustered
                             index, otherwise NULL */
    const ulint *offsets, /*!< in: rec_get_offsets(rec) */
    roll_ptr_t *roll_ptr) /*!< out: rollback pointer to the
                             inserted undo log record,
                             0 if BTR_NO_UNDO_LOG
                             flag was specified */ {
    dberr_t err;
    return err;
    // trx_assign_rseg_temp(trx);
    //
    // do {
    //     undo_block = buf_page_get_gen(page_id_t(undo->space, page_no),
    //                                   undo->page_size, RW_X_LATCH, undo->guess_block,
    //                                   Page_fetch::NORMAL, UT_LOCATION_HERE, &mtr);
    //

    /* When we add a page to an undo log, this is analogous to
    a pessimistic insert in a B-tree, and we must reserve the
    counterpart of the tree latch, which is the rseg mutex. */

    //     undo_ptr->rseg->latch();
    //     undo_block = trx_undo_add_page(trx, undo, undo_ptr, &mtr);
    //     undo_ptr->rseg->unlatch();
    // } while (undo_block != nullptr);
}


/** For an insert, checks the locks and does the undo logging if desired.
 @return DB_SUCCESS, DB_WAIT_LOCK, DB_FAIL, or error number */
[[nodiscard]] static inline dberr_t btr_cur_ins_lock_and_undo(
    ulint flags, /*!< in: undo logging and locking flags: if
                       not zero, the parameters index and thr
                       should be specified */
    btr_cur_t *cursor, /*!< in: cursor on page after which to insert */
    dtuple_t *entry, /*!< in/out: entry to insert */
    que_thr_t *thr, /*!< in: query thread or NULL */
    mtr_t *mtr, /*!< in/out: mini-transaction */
    bool *inherit) /*!< out: true if the inserted new record maybe
                        should inherit LOCK_GAP type locks from the
                        successor record */ {
    dberr_t err;
    roll_ptr_t roll_ptr;

    err = trx_undo_report_row_operation(flags, TRX_UNDO_INSERT_OP, thr, nullptr,
                                        entry, nullptr, 0, nullptr, nullptr,
                                        &roll_ptr);
}

/** Performs an insert on a page of an index tree. It is assumed that mtr
 holds an x-latch on the tree and on the cursor page. If the insert is
 made on the leaf level, to avoid deadlocks, mtr must also own x-latches
 to brothers of page, if those brothers exist.
 @return DB_SUCCESS or error number */
dberr_t btr_cur_pessimistic_insert(
    uint32_t flags, /*!< in: undo logging and locking flags: if not
                         zero, the parameter thr should be
                         specified; if no undo logging is specified,
                         then the caller must have reserved enough
                         free extents in the file space so that the
                         insertion will certainly succeed */
    btr_cur_t *cursor, /*!< in: cursor after which to insert;
                         cursor stays valid */
    ulint **offsets, /*!< out: offsets on *rec */
    mem_heap_t **heap, /*!< in/out: pointer to memory heap
                         that can be emptied, or NULL */
    dtuple_t *entry, /*!< in/out: entry to insert */
    rec_t **rec, /*!< out: pointer to inserted record if
                         succeed */
    big_rec_t **big_rec, /*!< out: big rec vector whose fields have to
                         be stored externally by the caller, or
                         NULL */
    que_thr_t *thr, /*!< in: query thread or NULL */
    mtr_t *mtr) /*!< in/out: mini-transaction */ {
    dberr_t err;
    /* Check locks and write to the undo log, if specified */
    bool inherit;
    err = btr_cur_ins_lock_and_undo(flags, cursor, entry, thr, mtr, &inherit);
}
