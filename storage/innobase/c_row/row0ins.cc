//
// Created by Arjun Sunil Kumar on 4/11/25.
//

#include "row0ins.h"

#include "data0data.h"
#include "../b2_que_later/que0que.h"
#include "row0sel.h"


dberr_t row_ins_clust_index_entry_low(uint32_t flags, ulint mode,
                                      dict_index_t *index, ulint n_uniq,
                                      dtuple_t *entry, que_thr_t *thr,
                                      bool dup_chk_only) {
}


/** Inserts an entry into a clustered index. Tries first optimistic,
 then pessimistic descent down the tree. If the entry matches enough
 to a delete marked record, performs the insert by updating or delete
 unmarking the delete marked record.
 @return DB_SUCCESS, DB_LOCK_WAIT, DB_DUPLICATE_KEY, or some other error code */
dberr_t row_ins_clust_index_entry(
    dict_index_t *index, /*!< in: clustered index */
    dtuple_t *entry,     /*!< in/out: index entry to insert */
    que_thr_t *thr,      /*!< in: query thread */
    bool dup_chk_only)
/*!< in: if true, just do duplicate check
and return. don't execute actual insert. */ {

    // err = row_ins_clust_index_entry_low(flags, BTR_MODIFY_LEAF, index, n_uniq, entry, thr, dup_chk_only);
}



/** Inserts an index entry to index. Tries first optimistic, then pessimistic
descent down the tree. If the entry matches enough to a delete marked record,
performs the insert by updating or delete unmarking the delete marked
record.
@param[in]      index           index to insert the entry
@param[in,out]  entry           entry to insert
@param[in,out]  multi_val_pos   if multi-value index, the start position
                                to insert next multi-value data,
                                and the returned value should be either
                                0 if all are done, or the position where the
                                insert failed. So return value of 0 could be
                                a bit ambiguous, however the return error
                                can help to see which case it is
@param[in]      thr             query thread
@return DB_SUCCESS, DB_LOCK_WAIT, DB_DUPLICATE_KEY, or some other error code */
static dberr_t row_ins_index_entry(dict_index_t *index, dtuple_t *entry,
                                   uint32_t &multi_val_pos, que_thr_t *thr) {

    // if (index->is_clustered()) {
    //     return (row_ins_clust_index_entry(index, entry, thr, false));
    // }
}


/** Sets the values of the dtuple fields in entry from the values of appropriate
columns in row.
@param[in]      index   index handler
@param[out]     entry   index entry to make
@param[in]      row     row
@return DB_SUCCESS if the set is successful */
dberr_t row_ins_index_entry_set_vals(const dict_index_t *index, dtuple_t *entry,
                                     const dtuple_t *row) {
}


/** Inserts a single index entry to the table.
 @return DB_SUCCESS if operation successfully completed, else error
 code or DB_LOCK_WAIT */
[[nodiscard]] static dberr_t row_ins_index_entry_step(
    ins_node_t *node, /*!< in: row insert node */
    que_thr_t *thr)   /*!< in: query thread */ {

    // err = row_ins_index_entry_set_vals(node->index, node->entry, node->row);
    //
    // if (err != DB_SUCCESS) {
    //     return err;
    // }

    // err = row_ins_index_entry(node->index, node->entry, node->ins_multi_val_pos, thr);

}



/** Inserts a row to a table.
 @return DB_SUCCESS if operation successfully completed, else error
 code or DB_LOCK_WAIT */
[[nodiscard]] static dberr_t row_ins(
    ins_node_t *node, /*!< in: row insert node */
    que_thr_t *thr)   /*!< in: query thread */ {

    // while (node->index != nullptr) {
    //     if (node->index->type != DICT_FTS) {
    //         err = row_ins_index_entry_step(node, thr);
    //     }
    //
    //     node->index = node->index->next();
    //     node->entry = UT_LIST_GET_NEXT(tuple_list, node->entry);
    //
    //     /* Skip corrupted secondary index and its entry */
    //     while (node->index && node->index->is_corrupted()) {
    //         node->index = node->index->next();
    //         node->entry = UT_LIST_GET_NEXT(tuple_list, node->entry);
    //     }
    // }
}



/** Inserts a row to a table. This is a high-level function used in SQL
 execution graphs.
 @return query thread to run next or NULL */
que_thr_t *row_ins_step(que_thr_t *thr) /*!< in: query thread */ {
    /* DO THE CHECKS OF THE CONSISTENCY CONSTRAINTS HERE */
    dberr_t err;
    ins_node_t *node = nullptr;
    err = row_ins(node, thr);

    return nullptr;
}
