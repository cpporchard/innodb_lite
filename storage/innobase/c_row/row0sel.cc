#include <strings.h>
struct btr_pcur_t;
/** Get the record buffer provided by the server, if there is one.
@param  prebuilt        prebuilt struct
@return the record buffer, or nullptr if none was provided */
static Record_buffer *row_sel_get_record_buffer(
    const row_prebuilt_t *prebuilt) {
    if (prebuilt->m_mysql_handler == nullptr) {
        return nullptr;
    }
    return prebuilt->m_mysql_handler->ha_get_record_buffer();
}

#include <cstddef>
/** Searches for rows in the database using cursor.
Function is mainly used for tables that are shared accorss connection and
so it employs technique that can help re-construct the rows that
transaction is suppose to see.
It also has optimization such as pre-caching the rows, using AHI, etc.

@param[out]     buf             buffer for the fetched row in MySQL format
@param[in]      mode            search mode PAGE_CUR_L
@param[in,out]  prebuilt        prebuilt struct for the table handler;
                                this contains the info to search_tuple,
                                index; if search tuple contains 0 field then
                                we position the cursor at start or the end of
                                index, depending on 'mode'
@param[in]      match_mode      0 or ROW_SEL_EXACT or ROW_SEL_EXACT_PREFIX
@param[in]      direction       0 or ROW_SEL_NEXT or ROW_SEL_PREV;
                                Note: if this is != 0, then prebuilt must has a
                                pcur with stored position! In opening of a
                                cursor 'direction' should be 0.
@return DB_SUCCESS or error code */
dberr_t row_search_mvcc(std::byte *buf, page_cur_mode_t mode,
                        row_prebuilt_t *prebuilt, ulint match_mode,
                        const ulint direction) {
    btr_pcur_t *pcur = prebuilt->pcur;

    /*-------------------------------------------------------------*/
    /* PHASE 1: Try to pop the row from the record buffer or from
    the prefetch cache */
    const auto record_buffer = row_sel_get_record_buffer(prebuilt);


    /*-------------------------------------------------------------*/
    /* PHASE 2: Try fast adaptive hash index search if possible */

    /* Next test if this is the special case where we can use the fast
    adaptive hash index to try the search. Since we must release the
    search system latch when we retrieve an externally stored field, we
    cannot use the adaptive hash index in a search in the case the row
    may be long and there may be externally stored fields */
    if (trx->mysql_n_tables_locked == 0 && !prebuilt->ins_sel_stmt &&
        prebuilt->select_lock_type == LOCK_NONE &&
        trx->isolation_level > TRX_ISO_READ_UNCOMMITTED &&
        MVCC::is_view_active(trx->read_view)) {
        rw_lock_s_lock(btr_get_search_latch(index), UT_LOCATION_HERE);

        switch (row_sel_try_search_shortcut_for_mysql(&rec, prebuilt, &offsets,
                                                      &heap, &mtr)) {
            case SEL_FOUND:
                if (prebuilt->idx_cond) {
                    switch (row_search_idx_cond_check(buf, prebuilt, rec, offsets)) {
                        case ICP_NO_MATCH:
                        case ICP_OUT_OF_RANGE:
                            goto shortcut_mismatch;
                        case ICP_MATCH:
                            goto shortcut_match;
                    }
                }
            shortcut_match:
                mtr_commit(&mtr);
                err = DB_SUCCESS;

                rw_lock_s_unlock(btr_get_search_latch(index));

            case SEL_EXHAUSTED:
            shortcut_mismatch:
                mtr_commit(&mtr);

            case SEL_RETRY:
                break;

            default:
                ut_d(ut_error);
        }
        mtr_commit(&mtr);
        mtr_start(&mtr);

        rw_lock_s_unlock(btr_get_search_latch(index));
        trx->has_search_latch = false;
    }

    /*-------------------------------------------------------------*/
    /* PHASE 3: Open or restore index cursor position */


    ut_ad(prebuilt->sql_stat_start || prebuilt->select_lock_type != LOCK_NONE ||
      MVCC::is_view_active(trx->read_view) || srv_read_only_mode);

    trx_start_if_not_started(trx, false, UT_LOCATION_HERE);

    thr = que_fork_get_first_thr(prebuilt->sel_graph);

    que_thr_move_to_run_state_for_mysql(thr, trx);

    if (prebuilt->select_lock_type == LOCK_NONE) {
        /* This is a consistent read */
        /* Assign a read view for the query */

        if (!srv_read_only_mode) {
            trx_assign_read_view(trx);
        }

        prebuilt->sql_stat_start = false;
    }

    /* Open or restore index cursor position */
    auto need_to_process = sel_restore_position_for_mysql(
        &same_user_rec, BTR_SEARCH_LEAF, pcur, moves_up, &mtr);

    pcur->m_btr_cur.thr = thr;


    pcur->open_no_init(index, search_tuple, mode, BTR_SEARCH_LEAF, 0, &mtr,
                       UT_LOCATION_HERE);

    pcur->m_trx_if_known = trx;

    rec = pcur->get_rec();

    pcur->open_at_side(mode == PAGE_CUR_G, index, BTR_SEARCH_LEAF, false, 0,
                       &mtr);

    rec_loop:

        if (trx_is_interrupted(trx)) {
            if (!spatial_search) {
                pcur->store_position(&mtr);
            }
            err = DB_INTERRUPTED;
            goto normal_return;
        }

    /*-------------------------------------------------------------*/
    /* PHASE 4: Look for matching records in a loop */

    rec = pcur->get_rec(); // <---- Core BTree function.

    ut_ad(page_rec_is_comp(rec) == comp);

    if (page_rec_is_infimum(rec) || page_rec_is_supremum(rec)) {
        goto next_rec;
    }

    /*-------------------------------------------------------------*/
    /* Do sanity checks in case our cursor has bumped into page
    corruption */


    /*-------------------------------------------------------------*/
    /* Calculate the 'offsets' associated with 'rec' */
    next_offs = rec_get_next_offs(rec, comp);

    offsets = rec_get_offsets(rec, index, offsets, ULINT_UNDEFINED,
                              UT_LOCATION_HERE, &heap);

    if (!rec_validate(rec, offsets) ||
        !btr_index_rec_validate(rec, index, false)) {
        goto next_rec;
        }

    /*  Note that we cannot trust the up_match value in the cursor at this
        place because we can arrive here after moving the cursor! Thus
        we have to recompare rec and search_tuple to determine if they
        match enough. */

    if (match_mode == ROW_SEL_EXACT) {
        /* Test if the index record matches completely to search_tuple
           in prebuilt: if not, then we return with DB_RECORD_NOT_FOUND */
        if (0 != cmp_dtuple_rec(search_tuple, rec, index, offsets)) {
            pcur->store_position(&mtr);
            pcur->m_rel_pos = BTR_PCUR_BEFORE;
            err = DB_RECORD_NOT_FOUND;
            goto normal_return;
        }
    } else if (match_mode == ROW_SEL_EXACT_PREFIX) {
        if (!cmp_dtuple_is_prefix_of_rec(search_tuple, rec, index, offsets)) {
            pcur->store_position(&mtr);
            pcur->m_rel_pos = BTR_PCUR_BEFORE;
            err = DB_RECORD_NOT_FOUND;
            goto normal_return;
        }
    }

    /* We are ready to look at a possible new index entry in the result
    set: the cursor is now placed on a user record */
    if (prebuilt->select_lock_type != LOCK_NONE) {
        auto row_to_range_relation = row_compare_row_to_range(
            set_also_gap_locks, trx, unique_search, index, clust_index, rec, comp,
            mode, direction, search_tuple, offsets, moves_up, prebuilt);

        err = sel_set_rec_lock(pcur, rec, index, offsets,
                               prebuilt->select_mode, prebuilt->select_lock_type,
                               LOCK_ORDINARY, thr, &mtr);

        if (err != DB_SUCCESS) {
            goto lock_wait_or_error;
        }

        if (!row_to_range_relation.row_can_be_in_range) {
            err = DB_RECORD_NOT_FOUND;
            goto normal_return;
        }
    } else {
        if (index == clust_index) {
            if (!lock_clust_rec_cons_read_sees(rec, index, offsets,
                                               trx_get_read_view(trx))) {
                err = row_sel_build_prev_vers_for_mysql(
                    trx->read_view, clust_index, prebuilt, rec, &offsets, &heap,
                    &rec, nullptr, &mtr, prebuilt->get_lob_undo());

                if (err != DB_SUCCESS || rec == nullptr) {
                    goto next_rec;
                }
                                               }
        } else {
            if (!lock_sec_rec_cons_read_sees(rec, index, trx->read_view)) {
                switch (row_search_idx_cond_check(buf, prebuilt, rec, offsets)) {
                    case ICP_NO_MATCH:
                        goto next_rec;
                    case ICP_OUT_OF_RANGE:
                        err = DB_RECORD_NOT_FOUND;
                    goto idx_cond_failed;
                    case ICP_MATCH:
                        goto requires_clust_rec;
                }
            }
        }
    }

    if (rec_get_deleted_flag(rec, comp)) {
        prebuilt->try_unlock(true);
        goto next_rec;
    }

    switch (row_search_idx_cond_check(buf, prebuilt, rec, offsets)) {
        case ICP_NO_MATCH:
            prebuilt->try_unlock(true);
        goto next_rec;
        case ICP_OUT_OF_RANGE:
            err = DB_RECORD_NOT_FOUND;
        prebuilt->try_unlock(true);
        goto idx_cond_failed;
        case ICP_MATCH:
            break;
    }
    if (index != clust_index && prebuilt->need_to_access_clustered) {
        requires_clust_rec:
          err = row_sel_get_clust_rec_for_mysql(
              prebuilt, index, rec, thr, &clust_rec, &offsets, &heap,
              nullptr, &mtr, prebuilt->get_lob_undo());

        if (err != DB_SUCCESS || clust_rec == nullptr ||
            rec_get_deleted_flag(clust_rec, comp)) {
            prebuilt->try_unlock(true);
            goto next_rec;
            }

        result_rec = clust_rec;
    } else {
        result_rec = rec;
    }

    if (!row_sel_store_mysql_rec(buf, prebuilt, result_rec, nullptr,
                             result_rec != rec,
                             result_rec != rec ? clust_index : index,
                             prebuilt->index, offsets, false,
                             nullptr, prebuilt->blob_heap)) {
        goto next_rec;
                             }

    err = DB_SUCCESS;

    idx_cond_failed:
    if (!unique_search || !index->is_clustered() || direction != 0 ||
        prebuilt->select_lock_type != LOCK_NONE || prebuilt->used_in_HANDLER ||
        prebuilt->innodb_api) {
        pcur->store_position(&mtr);
        }

    goto normal_return;

    next_rec:
    prev_vrow = vrow;
    vrow = nullptr;
    end_loop++;
    goto rec_loop;

    /*-------------------------------------------------------------*/
    /* PHASE 5: Move the cursor to the next index record */

    /* NOTE: For moves_up==false, the mini-transaction will be
    committed and restarted every time when switching b-tree
    pages. For moves_up==true in index condition pushdown, we can
    scan an entire secondary index tree within a single
    mini-transaction. As long as the prebuilt->idx_cond does not
    match, we do not need to consult the clustered index or
    return records to MySQL, and thus we can avoid repositioning
    the cursor. What prevents us from buffer-fixing all leaf pages
    within the mini-transaction is the btr_leaf_page_release()
    call in btr_pcur::move_to_next_page(). Only the leaf page where
    the cursor is positioned will remain buffer-fixed.
    For R-tree spatial search, we also commit the mini-transaction
    each time  */

    if (mtr_has_extra_clust_latch || spatial_search) {
        /* If we have extra cluster latch, we must commit
        mtr if we are moving to the next non-clustered
        index record, because we could break the latching
        order if we would access a different clustered
        index page right away without releasing the previous. */

        bool is_pcur_rec = (pcur->get_rec() == prev_rec);

        /* No need to do store restore for R-tree */
        if (!spatial_search) {
            pcur->store_position(&mtr);
        }

        mtr_commit(&mtr);
        mtr_has_extra_clust_latch = false;

        DEBUG_SYNC_C("row_search_before_mtr_restart_for_extra_clust");

        mtr_start(&mtr);

        if (!spatial_search) {
            const auto result = sel_restore_position_for_mysql(
                &same_user_rec, BTR_SEARCH_LEAF, pcur, moves_up, &mtr);

            if (result) {
                prev_rec = nullptr;
                goto rec_loop;
            }

        }

        if (moves_up) {
            bool move;

            if (!spatial_search) {
                move = pcur->move_to_next(&mtr); // <---- BTREE
            }
        }


    }
}
