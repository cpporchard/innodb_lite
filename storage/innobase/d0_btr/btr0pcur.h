//
// Created by Arjun Sunil Kumar on 4/5/25.
//

#ifndef BTR0PCUR_H
#define BTR0PCUR_H
#include <cstddef>

/* The persistent B-tree cursor structure. This is used mainly for SQL
selects, updates, and deletes. */
typedef std::byte rec_t;

struct btr_pcur_t {
    /** Sets the old_rec_buf field to nullptr.
        @param[in]  read_level  read level where the cursor would be positioned or
        re-positioned. */
    void init(size_t read_level = 0);

    /** @return the index of this persistent cursor */
    dict_index_t *index() { return (m_btr_cur.index); }


    /** Opens a persistent cursor at either end of an index.
        @param[in]        from_left   True if open to the low end, false
                                    if to the high end.
        @param[in]        index                   Index
        @param[in]        latch_mode  Latch mode
        @param[in]        init_pcur     Whether to initialize pcur.
        @param[in]        level                   Level to search for (0=leaf).
        @param[in,out]        mtr                   Mini-transaction */
    void open_at_side(bool from_left, dict_index_t *index, ulint latch_mode,
                      bool init_pcur, ulint level, mtr_t *mtr);

    /** Opens a persistent cursor at first leaf page (low end). It will not call
        init().
        @param[in]        index                   Index
        @param[in]        latch_mode  Latch mode
        @param[in,out]        mtr                   Mini-transaction */
    void begin_leaf(dict_index_t *index, ulint latch_mode, mtr_t *mtr) {
        open_at_side(true, index, latch_mode, false, 0, mtr);
    }

    /** Initializes and opens a persistent cursor to an index tree
         It should be closed with btr_pcur::close.
         @param[in]     index                 Index.
         @param[in]     level                 Level in the btree.
         @param[in]     tuple                 Tuple on which search done.
         @param[in]     mode                  PAGE_CUR_L, ...; NOTE that if the search
         is made using a unique prefix of a record, mode should be PAGE_CUR_LE, not
         PAGE_CUR_GE, as the latter may end up on the previous page from the record!
         @param[in]     latch_mode        BTR_SEARCH_LEAF, ...
         @param[in]     mtr                     Mini-transaction.
         @param[in]     location                  Location where called. */
    void open(dict_index_t *index, ulint level, const dtuple_t *tuple,
              page_cur_mode_t mode, ulint latch_mode, mtr_t *mtr,
              ut::Location location);

    /** Restores the stored position of a persistent cursor bufferfixing
    the page and obtaining the specified latches. If the cursor position
    was saved when the
    (1) cursor was positioned on a user record: this function restores
    the position to the last record LESS OR EQUAL to the stored record;
    (2) cursor was positioned on a page infimum record: restores the
    position to the last record LESS than the user record which was the
    successor of the page infimum;
    (3) cursor was positioned on the page supremum: restores to the first
    record GREATER than the user record which was the predecessor of the
    supremum.
    (4) cursor was positioned before the first or after the last in an
    empty tree: restores to before first or after the last in the tree.
    @param[in]        latch_mode  BTR_SEARCH_LEAF, ...
    @param[in,out]  mtr                 Mini-transaction
    @param[in]        location            Location where called.
    @return true if the cursor position was stored when it was on a user
            record and it can be restored on a user record whose ordering
            fields are identical to the ones of the original user record */
    bool restore_position(ulint latch_mode, mtr_t *mtr, ut::Location location);

    /** Frees the possible memory heap of a persistent cursor and
    sets the latch mode of the persistent cursor to BTR_NO_LATCHES.
    WARNING: this function does not release the latch on the page where the
    cursor is currently positioned. The latch is acquired by the
    "move to next/previous" family of functions. Since recursive shared
    locks are not allowed, you must take care (if using the cursor in
    S-mode) to manually release the latch by either calling
    btr_leaf_page_release(pcur.get_block(), pcur.latch_mode, mtr)
    or by committing the mini-transaction right after btr_pcur::close().
    A subsequent attempt to crawl the same page in the same mtr would
    cause an assertion failure. */
    void close();

    /** @return the btree cursor (const version). */
    const btr_cur_t *get_btr_cur() const;

    /** @return the btree cursor (non const version). */
    btr_cur_t *get_btr_cur();

    /** @return the btree page cursor (non const version). */
    page_cur_t *get_page_cur();

    /** @return the btree cursor (const version). */
    const page_cur_t *get_page_cur() const;

    /** Returns the page of a persistent pcur (non const version).
    @return pointer to the page */
    page_t *get_page();

    /** Returns the current record (const version).
    @return pointer to the record */
    const rec_t *get_rec() const;
};



inline bool btr_pcur_t::move_to_next(mtr_t *mtr) {
    ut_ad(m_pos_state == BTR_PCUR_IS_POSITIONED);
    ut_ad(m_latch_mode != BTR_NO_LATCHES);

    m_old_stored = false;

    if (is_after_last_on_page()) {
        if (is_after_last_in_tree(mtr)) {
            return (false);
        }

        move_to_next_page(mtr);

        return (true);
    }

    move_to_next_on_page();

    return (true);
}


#endif //BTR0PCUR_H